<div align="center">

# Simple-Tokenizer

A lightweight, high-performance C library for tokenizing strings. It efficiently breaks down input strings into tokens based on a set of delimiter characters.

## Overview

**Simple-Tokenizer** is a single-header C library that provides fast string tokenization with minimal overhead. It's designed to be simple, efficient, and easy to integrate into your C projects.

### Key Features

</div>

- **Zero-Copy Tokenization**: Operates in-place on the input string (modifies it destructively)
- **High Performance**: Optimized for speed with minimal memory allocations
- **Flexible**: Optional caller-provided token buffer or automatic allocation
- **Small Footprint**: Single header file library with no external dependencies
- **Standard C**: Compatible with ANSI C and standard library functions

<div align="center">

## Usage

### Basic Example

</div>

```c
#include "Simple-Tokenizer/inc.h"
#include <stdio.h>

int main(void) {
    char str[] = "hello;world;tokenizer";
    size_t token_count = 0;
    
    // Tokenize the string using ';' as delimiter
    st_token* tokens = st_tknstr(
        NULL,                    // out: allocate buffer automatically
        100,                     // max: maximum tokens to extract
        &token_count,            // tto: output token count
        ";",                     // rej: reject string (delimiters)
        str                      // str: input string
    );
    
    // Print tokens
    for (size_t i = 0; i < token_count; i++) {
        printf("Token %zu: %s (length: %zu)\n", 
               i, tokens[i].str, tokens[i].len);
    }
    
    free(tokens);
    return 0;
}
```

<div align="center">

### API Reference

#### Token Structure

</div>

```c
typedef struct st_token_t {
    char*  str;  // Null-terminated pointer to token substring
    size_t len;  // Total byte size of token
} st_token;
```

<div align="center">

#### Tokenization Function

</div>

```c
st_token* st_tknstr(
    st_token* out,              // Optional: pre-allocated token buffer (NULL = allocate)
    const size_t max,           // Maximum tokens to generate
    size_t* const tto,          // Optional: output parameter for total token count
    const char* const rej,      // Null-terminated reject string (delimiters)
    char* const __restrict str  // Null-terminated input string to tokenize
);
```

<div align="center">

**Parameters:**

</div>

- `out`: Optional caller-provided buffer for tokens. If `NULL`, the function allocates memory.
- `max`: Maximum number of tokens to extract.
- `tto`: Pointer to store the total number of tokens generated. Can be `NULL` if count is not needed.
- `rej`: String containing delimiter characters (e.g., `";"`, `" \t\n"`).
- `str`: The input string to tokenize (will be modified destructively).

<div align="center">

**Returns:** Pointer to the token buffer (either provided or allocated).

**Warnings:**

</div>

- This function modifies the input string by inserting null terminators.
- If `out` is `NULL`, the function allocates memory that must be freed by the caller using `free()`.

<div align="center">

## Project Structure

</div>

```
.src/
├── Simple-Tokenizer/
│   ├── inc.h           # Main include file (includes entire library)
│   ├── tokenizer.h     # Tokenization function implementation
│   ├── token.h         # Token structure definition
│   └── defines.h       # Platform-specific macros
└── benchmark.c         # Performance benchmark utility
```

<div align="center">

## Performance

The library includes a benchmark utility that measures tokenization performance across various input sizes. Run it with:

</div>

```bash
./st_bench
```

<div align="center">

The benchmark generates test strings with increasing token counts and reports:

</div>

- Throughput in MB/s
- Tokenization speed in million tokens/second
- Total processing time

<div align="center">

## Compilation

Since this is a header-only library, simply include `Simple-Tokenizer/inc.h` in your project:

</div>

```c
#include "Simple-Tokenizer/inc.h"
```

<div align="center">

### Compiling with GCC/Clang

</div>

```bash
gcc -O3 -Wall -o myapp myapp.c
```

<div align="center">

### Compiling the Benchmark

</div>

```bash
gcc -O3 -Wall -o st_bench .src/benchmark.c
```

<div align="center">

## Dependencies

</div>

- **Standard C Library** (`string.h`, `malloc.h`)
- **ANSI C** compatible compiler

<div align="center">

## Memory Management

</div>

- **Automatic Allocation**: When `out` is `NULL`, the function calculates the exact number of tokens needed and allocates a single buffer.
- **Manual Allocation**: Provide your own buffer to avoid dynamic allocation.
- **Caller Responsibility**: If the function allocates memory, the caller must free it using `free()`.

<div align="center">

## Implementation Notes

</div>

- **Destructive Tokenization**: The function modifies the input string by replacing delimiter characters with null terminators. If you need to preserve the original string, make a copy first.
- **Contiguous Allocation**: All tokens are stored in a single contiguous memory block, improving cache locality.
- **No External Dependencies**: Uses only standard C library functions.

<div align="center">

## License

Refer to the repository for licensing information.

## Contributing

Contributions are welcome! Feel free to submit issues and pull requests to improve the library.

</div>
