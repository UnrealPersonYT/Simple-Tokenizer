/// @file  Simple-Tokenizer/tokenizer.h
/// @brief Contains the tokenizer function
#pragma once
#include "string.h" // You can implement your own string functions
#include "malloc.h" // You can implement your own memory functions

/// @brief     Tokenizes a null-terminated input string
/// @param out Optional caller-provided char* buffer (NULL = allocate internally)
/// @param max Max tokens to generate
/// @param tto Output: total tokens generated (NULL = dont save output)
/// @param rej Pointer to null-terminated reject string (Characters that terminate a token)
/// @param str Pointer to null-terminated string to tokenize
/// @return    Pointer to char* buffer, could be NULL because of malloc error
/// @warning   This function null-terminates tokens by modifying the input string destructively
/// @warning   If `out` is NULL, this function allocates a token buffer.
///            The caller is responsible for freeing it with free().
/// @note      Returns null if str or rej are NULL
char** st_tknstr(char** out, const size_t max, size_t* const tto, const char* const __restrict rej, char* const __restrict str){
    if(!str || !rej) // Return if null pointers
        return NULL;

    const size_t strl = strlen(str); // Size of string in bytes
    if(!strl) // Return if empty string
        return NULL;

    if(out == NULL){ // Allocate new buffer
        size_t size = 0;
        for(size_t stri = 0; size < max && stri < strl; stri += strspn(&str[stri], rej), ++size)
            stri += strcspn(&str[stri], rej) + 1;
        if(!size)
            return NULL;
        out = malloc(size * sizeof(char*));
        if(!out) // Return if malloc error
            return NULL;
    }

    size_t tt = 0; // Total tokens
    for(size_t stri = 0; tt < max && stri < strl; stri += strspn(&str[stri], rej)){
        const size_t len = strcspn(&str[stri], rej);
        str[stri + len] = '\0';
        out[tt++] = &str[stri];
        stri += len + 1;
    }

    if(tto)
        *tto = tt;
    
    return out;
}