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

int main(void){
    char str[] = "hello;world;tokenizer";
    size_t token_count = 0;
    
    // Tokenize the string using ';' as delimiter
    char** tokens = st_tknstr(
        NULL,                    // out: allocate buffer automatically
        100,                     // max: maximum tokens to extract
        &token_count,            // tto: output token count
        ";",                     // rej: reject string (delimiters)
        str,                     // str: input string
        sizeof(str)              // stl: size of string (0 = compute internally)
    );
    
    // Print tokens
    for(size_t i = 0; i < token_count; i++)
        printf("Token %zu: %s\n", i, tokens[i]);
    
    free(tokens);
    return 0;
}
```

#### Tokenization Function & Utilities

</div>

```c
char** st_tknstr(
    char** out,                 // Optional caller-provided char* buffer (NULL = allocate internally)
    const size_t max,           // Max tokens to generate
    size_t* const tto,          // Output: total tokens generated (NULL = dont save output)
    const char* const rej,      // Pointer to null-terminated reject string (Characters that terminate a token)
    char* const __restrict str, // Pointer to null-terminated string to tokenize
    size_t stl                  // Length of input string in bytes (0 = calculate internally)
);
size_t st_tkncnt(
    const char* const __restrict str, // Pointer to null-terminated string to tokenize
    const char* const __restrict rej, // Pointer to null-terminated reject string (Characters that terminate a token)
    const size_t max,                 // Max tokens to count
    size_t stl                        // Length of input string in bytes (0 = calculate internally)
);
```

<div align="center">

**Parameters:**

</div>

- `out`: Optional caller-provided buffer for tokens. If `NULL`, the function allocates memory internally.
- `max`: Maximum number of tokens to extract.
- `tto`: Pointer to store the total number of tokens generated. Can be `NULL` if count is not needed.
- `rej`: Pointer to null-terminated string containing delimiter characters (e.g., `";"`, `" \t\n"`).
- `str`: Pointer to null-terminated string to tokenize (will be modified destructively).
- `stl`: Length of input string in bytse. Can be `0` to compute internaly; 

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
│   ├── tokenizer.h     # Tokenization function implementation & utilities
│   ├── string.h        # String functions (uses stdlib by default, customizable)
│   └── malloc.h        # Memory allocation (uses stdlib by default, customizable)
└── benchmark.c         # Performance benchmark utility
```

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

This project uses a cross-platform Makefile that auto-detects the best available compiler.

### Quick Build

```bash
make
```

This will automatically detect and use g++, clang, or cl (MSVC) in order of preference.

### Build Options

```bash
make                      # Build with auto-detected compiler
make CC=clang             # Use clang compiler
make TARGET=myapp         # Set custom output name
make CC=clang TARGET=app  # Combine options
make clean                # Remove build artifacts
make help                 # Show help message
make info                 # Show build configuration
```

### Manual Compilation

If you prefer not to use make:

```bash
# Windows
gcc -O3 -Wall -Wextra -std=c99 -I.src -o st_bench.exe .src/benchmark.c

# Linux/macOS
gcc -O3 -Wall -Wextra -std=c99 -I.src -o st_bench .src/benchmark.c
```

<div align="center">

## Custom Implementations

You can customize string and memory functions for embedded systems or performance tuning:

</div>

1. Create custom `string.h` in `.src/Simple-Tokenizer/`:
```c
#pragma once
// Your custom strcspn, strspn implementations
size_t strcspn(const char* s, const char* reject) { /* ... */ }
size_t strspn(const char* s, const char* accept) { /* ... */ }
```

2. Create custom `malloc.h` in `.src/Simple-Tokenizer/`:
```c
#pragma once
// Your custom allocator
void* malloc(size_t size) { /* ... */ }
void free(void* ptr) { /* ... */ }
```

The library will automatically use your implementations instead of stdlib.

<div align="center">

## Dependencies

</div>

- **C Compiler**: gcc, clang, or MSVC (auto-detected by Makefile)
- **Make**: For automated builds (optional, manual compilation supported)
- **Standard C Library**: `string.h`, `malloc.h` (or custom implementations)

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
