#include "Simple-Tokenizer/inc.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Portable C timer (ANSI C)
static double now_sec(void){
    return (double)clock() / (double)CLOCKS_PER_SEC;
}

// Generate random string with variable token length, null-terminated
static char* make_random_buffer(size_t total_bytes, size_t* out_len){
    char* buf = malloc(total_bytes + 1);
    if(!buf)
        return NULL;
    
    srand(12345); // Fixed seed for reproducibility
    size_t pos = 0;
    
    while(pos < total_bytes){
        // Random token length (1-20 chars)
        size_t token_len = 1 + (rand() % 20);
        if(pos + token_len > total_bytes)
            token_len = total_bytes - pos;
        
        // Fill with random chars (avoid null and semicolon)
        for(size_t i = 0; i < token_len && pos < total_bytes; i++){
            char c = 'a' + (rand() % 26);
            buf[pos++] = c;
        }
        
        // Add separator if room
        if(pos < total_bytes)
            buf[pos++] = ';';
    }
    
    buf[pos] = '\0';
    *out_len = pos;
    return buf;
}

int main(void){
    printf("\n=== FAIR COMPARISON: Randomized Input ===\n");
    printf("Input: Truly random with variable token lengths (1-20 chars)\n");
    printf("Separator: semicolon\n\n");
    
    // Use largest size (2^27 tokens)
    const size_t target_size = (1u << 27);
    size_t buflen = 0;
    
    printf("--- Generating random buffer (~%zu bytes) ---\n", target_size);
    char* buf = make_random_buffer(target_size, &buflen);
    if(!buf){
        printf("Allocation failed\n");
        return 1;
    }
    
    // Count actual tokens in randomized buffer
    size_t actual_tokens = st_tkncnt(buf, ";", SIZE_MAX, buflen);
    
    printf("Actual buffer length: %zu bytes\n", buflen);
    printf("Actual token count: %zu\n\n", actual_tokens);
    
    // ===== PHASE 1: Allocation only =====
    printf("--- PHASE 1: Allocation Only ---\n");
    double alloc_t0 = now_sec();
    char** out = malloc(actual_tokens * sizeof(char*));
    double alloc_t1 = now_sec();
    double alloc_time = alloc_t1 - alloc_t0;
    printf("Allocation time: %.9f sec\n\n", alloc_time);
    
    // ===== PHASE 2: Tokenization only (with pre-allocated buffer) =====
    printf("--- PHASE 2: Tokenization Only (pre-allocated buffer) ---\n");
    
    // Make fresh copy for tokenization
    char* buf_copy = malloc(buflen + 1);
    memcpy(buf_copy, buf, buflen + 1);
    
    size_t tno = 0;
    char** buf_out = malloc(actual_tokens * sizeof(char*));
    double tok_t0 = now_sec();
    st_tknstr(buf_out, actual_tokens, &tno, ";", buf_copy, buflen);
    double tok_t1 = now_sec();
    double tok_time = tok_t1 - tok_t0;
    
    double mbps = (double)buflen / tok_time / (1024.0 * 1024.0);
    double mtok = (double)tno / tok_time / 1e6;
    
    printf("Tokenization time: %.9f sec\n", tok_time);
    printf("Tokens parsed: %zu\n", tno);
    printf("Throughput: %.2f MB/s\n", mbps);
    printf("Token rate: %.2f million tokens/sec\n\n", mtok);
    free(buf_out);
    
    // ===== PHASE 3: Full operation (allocation + tokenization) =====
    printf("--- PHASE 3: Full Operation (Allocation + Tokenization) ---\n");
    
    char* buf_copy2 = malloc(buflen + 1);
    memcpy(buf_copy2, buf, buflen + 1);
    
    double full_t0 = now_sec();
    char** out2 = st_tknstr(NULL, actual_tokens, &tno, ";", buf_copy2, buflen);
    double full_t1 = now_sec();
    double full_time = full_t1 - full_t0;
    
    double full_mbps = (double)buflen / full_time / (1024.0 * 1024.0);
    double full_mtok = (double)tno / full_time / 1e6;
    
    printf("Full operation time: %.9f sec\n", full_time);
    printf("Tokens parsed: %zu\n", tno);
    printf("Throughput: %.2f MB/s\n", full_mbps);
    printf("Token rate: %.2f million tokens/sec\n", full_mtok);
    
    // Cleanup
    free(buf);
    free(buf_copy);
    free(buf_copy2);
    free(out);
    free(out2);
    
    return 0;
}