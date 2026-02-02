/// @file  Simple-Tokenizer/string.h
/// @brief Contains the string utility functions
#pragma once
#include <string.h> // For strlen
#include <stddef.h>

size_t strspn(const char* const __restrict str, const char* const __restrict acc){
    size_t count = 0;
    for(char strc = *str; strc ; strc = str[count]){
        char rejc = *acc;
        for(size_t rec = 0; rejc && strc != rejc; rejc = acc[++rec]);
        if(rejc != '\0')
            break;
        ++count;
    }
    return count;
}

size_t strcspn(const char* const __restrict str, const char* const __restrict rej){
    size_t count = 0;
    for(char strc = *str; strc ; strc = str[count]){
        char rejc = *rej;
        for(size_t rec = 0; rejc && strc != rejc; rejc = rej[++rec]);
        if(rejc == '\0')
            break;
        ++count;
    }
    return count;
}