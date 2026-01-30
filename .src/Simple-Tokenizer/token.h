/// @file  Simple-Tokenizer/token.h
/// @brief Contains the token data structure & utilities
#pragma once
#include "string.h" // You can implement your own string functions
#include "malloc.h" // You can implement your own memory functions

/// @brief The Simple-Tokenizer library's main token type that is parsed on a given string
typedef struct st_token_t{
    char*  str; // Null-terminated pointer to input substring
    size_t len; // Total byte size of string
}st_token;