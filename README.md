# sv128: A Simulated Vector Library

A C++ library for simulating vector operations with multiple high-performance implementations using SSE and AVX intrinsics.

## Features

- Multiple implementation backends:
  - **Scalar**: Portable C++ implementation using for-loops (4-wide vectors)
  - **SSE**: High-performance SSE4.1 intrinsics implementation (4-wide vectors)
  - **AVX**: High-performance AVX/AVX2 intrinsics implementation (8-wide vectors)
- C-style API mimicking SIMD instruction sets (sv_int_add, sv_load_int, etc.)
- Masking support for conditional operations
- Built-in performance logger to track vector lane utilization
- Static library format for easy integration
- Compile-time implementation selection via make variables

## How to Build

The library supports three different implementations that can be selected at compile time:

### Scalar Implementation (Default)
```bash
make
# or explicitly:
make IMPL=SCALAR
```
This builds the portable C++ implementation using standard for-loops. Compatible with all systems.

### SSE Implementation
```bash
make IMPL=SSE
```
This builds the SSE4.1 intrinsics implementation for enhanced performance on x86/x64 systems with SSE4.1 support.

### AVX Implementation
```bash
make IMPL=AVX
```
This builds the AVX/AVX2 intrinsics implementation for maximum performance on modern x86/x64 systems with AVX2 support. Uses 8-wide vectors instead of 4-wide.

### Build Information
To see the current build configuration:
```bash
make info
```

To clean all build artifacts:
```bash
make clean
```

## How to Install

To install the library and headers to `/usr/local` by default:

```bash
make install
```

To install to a different location, use the `PREFIX` variable:

```bash
make install PREFIX=/path/to/your/dir
```

To uninstall the library:

```bash
make uninstall PREFIX=/path/to/your/dir
```

## How to Use

To use the sv128 library in your own projects:

1. Include the header:
   ```cpp
   #include <sv128/sv128.h>
   ```

2. When compiling your project, link against the library:
   ```bash
   g++ your_app.cpp -L/path/to/lib -lsv128 -I/path/to/include -o your_app
   ```

## Example

An example program `test_app` is built automatically when you run `make`. Run it with:

```bash
./test_app
```

This demonstrates the library's features and shows the performance logger output.

## API Reference

This section provides a brief overview of the sv128 library functions. For a detailed description of each function, please see [API_DOCS.md](API_DOCS.md).

### Data Types

- `sv_mask`: A vector mask with VECTOR_WIDTH boolean lanes.
- `sv_int4`: A vector register with VECTOR_WIDTH integer lanes (4 for Scalar/SSE, 8 for AVX).
- `sv_float4`: A vector register with VECTOR_WIDTH float lanes (4 for Scalar/SSE, 8 for AVX).

**Note**: For AVX builds, the library also defines `sv_int8` and `sv_float8` types, but `sv_int4` and `sv_float4` are aliased to these for API compatibility.

### Memory & Set Operations

- `sv_int4 sv_load_int(const int* mem_addr)`: Loads VECTOR_WIDTH integers from memory.
- `void sv_store_int(int* mem_addr, sv_int4 a)`: Stores a vector to memory.
- `sv_int4 sv_set_int(int i0, ...)`: Creates a vector with explicitly provided values.
- `sv_int4 sv_set1_int(int val)`: Creates a vector with all lanes set to the same value.

(Equivalent functions exist for float type.)

### Vector Arithmetic

- `sv_int4 sv_int_add(sv_int4 a, sv_int4 b)`: Element-wise addition.
- `sv_int4 sv_int_sub(sv_int4 a, sv_int4 b)`: Element-wise subtraction.
- `sv_int4 sv_int_mul(sv_int4 a, sv_int4 b)`: Element-wise multiplication.
- `sv_int4 sv_int_div(sv_int4 a, sv_int4 b)`: Element-wise division.
- `sv_int4 sv_int_abs(sv_int4 a)`: Element-wise absolute value.

(Equivalent functions exist for float type.)

### Advanced Vector Operations

- `sv_float4 sv_float_hadd(sv_float4 a)`: Horizontal add. [a,b,c,d] -> [a+b, a+b, c+d, c+d].
- `sv_float4 sv_float_interleave(sv_float4 a)`: Interleaves elements. [a,b,c,d] -> [a,c,b,d].

### Vector Comparison

- `sv_mask sv_int_gt(sv_int4 a, sv_int4 b)`: Element-wise greater-than comparison.
- `sv_mask sv_int_lt(sv_int4 a, sv_int4 b)`: Element-wise less-than comparison.
- `sv_mask sv_int_eq(sv_int4 a, sv_int4 b)`: Element-wise equality comparison.

(Equivalent functions exist for float type.)

### Mask Operations

- `sv_mask sv_init_ones(int first_n)`: Creates a mask with the first n lanes set to true.
- `sv_mask sv_mask_not(sv_mask a)`: Inverts a mask.
- `sv_mask sv_mask_or(sv_mask a, sv_mask b)`: Logical OR on two masks.
- `sv_mask sv_mask_and(sv_mask a, sv_mask b)`: Logical AND on two masks.
- `int sv_cntbits(sv_mask a)`: Counts the number of true lanes in a mask.

### Masked Arithmetic

- `sv_int4 sv_int_masked_add(sv_int4 a, sv_int4 b, sv_mask mask)`: Performs addition only on lanes where the mask is true.

(Similar functions exist for subtraction, multiplication, and for the float type.)

### Logger Functions

- `void sv_logger_init()`: Resets all performance counters.
- `void sv_logger_print_stats()`: Prints the final performance statistics.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgements

The prototype for this library is based on the homework assignment code from the Parallel Programming (Fall 2023, pp-23) course taught by Professor Yi-Ping You at NYCU.

This project's structure and code were also bootstrapped with the assistance of AI. Special thanks to the following models for their contributions:

- Google's Gemini 2.5 Pro
- Anthropic's Claude 3 Sonnet via Copilot