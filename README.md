# MyMalloc Project

## Project Overview

The `mymalloc` project implements a custom memory allocation system similar to the `malloc` and `free` functions in C. It provides functionality for dynamic memory allocation, deallocation, and memory management using a static array. This implementation includes testing suites to verify the correctness and robustness of the allocation and deallocation operations.

## Features

- Custom implementation of `myMalloc()` and `myFree()` functions.
- Memory is managed using a fixed-size static array (`memory`) of 512 bytes.
- Headers are used to track the size and allocation status of memory chunks.
- Includes support for:
  - Allocation of memory in aligned 8-byte chunks.
  - Coalescing of adjacent free chunks during deallocation.
  - Error handling for invalid free operations.
- Testing functions for various scenarios to ensure memory management correctness.

## Technologies Used

- C Programming Language
- Standard libraries: `<stdio.h>`, `<stdlib.h>`

## Project Structure

- `mymalloc.c`: Contains the implementation of `myMalloc()` and `myFree()` functions.
- `mymalloc.h`: Header file with function declarations and macros.
- `Makefile`: Used to compile the project.
- `memgrind.c`: Test cases and benchmarks for the memory allocator.

## Compilation and Execution


# Compile the project
```bash
make
```

# Run the program
```bash
./mymalloc.exe
```
