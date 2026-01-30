#include "Simple-Tokenizer/inc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Portable C timer (ANSI C)
static double now_sec(void){
    return (double)clock() / (double)CLOCKS_PER_SEC;
}

// Generate a buffer with N tokens: "aaaa;aaaa;aaaa;..."
static char* make_buffer(size_t tokens, size_t* out_len){
    const char* word = "aaaa";
    const size_t wlen = 4;
    const size_t sep  = 1;

    size_t total = tokens * (wlen + sep);
    char* buf = malloc(total + 1);
    if(!buf)
        return NULL;
    char* p = buf;
    for(size_t i = 0; i < tokens; i++){
        memcpy(p, word, wlen);
        p += wlen;
        *p++ = ';';
    }
    buf[total] = '\0';
    *out_len = total;
    return buf;
}

int main(void){
    const size_t start_pow = 27;
    const size_t end_pow   = 20;
    for(size_t p = start_pow; p >= end_pow; p--){
        size_t tokens = (size_t)1 << p;
        size_t buflen = 0;
        printf("\n--- Benchmark: 2^%zu = %zu tokens ---\n", p, tokens);
        char* buf = make_buffer(tokens, &buflen);
        if(!buf){
            printf("Allocation failed\n");
            return 1;
        }
        size_t tno = 0;
        double t0 = now_sec();
        st_token* out = st_tknstr(NULL, tokens, &tno, ";", buf);
        double t1 = now_sec();
        double dt = t1 - t0;
        double mbps = (double)buflen / dt / (1024.0 * 1024.0);
        double mtok = (double)tno / dt / 1e6;
        printf("Parsed tokens: %zu\n", tno);
        printf("Time: %.6f sec\n", dt);
        printf("Throughput: %.2f MB/s\n", mbps);
        printf("Token rate: %.2f million tokens/sec\n", mtok);
        free(out);
        free(buf);
    }
    return 0;
}