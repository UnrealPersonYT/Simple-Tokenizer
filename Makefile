# Simple-Tokenizer Cross-OS Makefile
# Usage:
#   make                    Build with auto-detected compiler
#   make CC=clang           Override compiler
#   make TARGET=myapp       Set output name
#   make clean              Remove build
#   make help               Show help

# Auto-detect best available compiler
ifeq ($(CC),)
    ifeq ($(OS),Windows_NT)
        ifeq ($(shell where g++ 2>nul),)
            ifeq ($(shell where clang 2>nul),)
                CC = cl
            else
                CC = clang
            endif
        else
            CC = g++
        endif
    else
        ifeq ($(shell which g++ 2>/dev/null),)
            CC = clang
        else
            CC = g++
        endif
    endif
endif

# Configuration
TARGET ?= st_bench
CFLAGS ?= -O3 -Wall -Wextra -std=c99 -s
SOURCES = .src/benchmark.c

# Platform detection for cleanup
ifeq ($(OS),Windows_NT)
    PLATFORM = Windows
    RM = del /Q
    EXE = $(TARGET).exe
else
    PLATFORM = Unix
    RM = rm -f
    EXE = $(TARGET)
endif

# Build rules
.PHONY: all clean help info

all: $(EXE)

$(EXE): $(SOURCES)
	$(CC) $(CFLAGS) -I.src -o $@ $^

clean:
ifeq ($(PLATFORM),Windows)
	@if exist $(EXE) $(RM) $(EXE)
else
	@$(RM) $(EXE)
endif
	@echo Cleaned

help:
	@echo.
	@echo Simple-Tokenizer Makefile
	@echo ==========================
	@echo Usage: make [CC=compiler] [TARGET=name] [CFLAGS=flags]
	@echo.
	@echo Examples:
	@echo   make
	@echo   make CC=clang
	@echo   make TARGET=myapp CC=clang
	@echo.

info:
	@echo Compiler: $(CC)
	@echo Target: $(EXE)
	@echo Platform: $(PLATFORM)
	@echo.
