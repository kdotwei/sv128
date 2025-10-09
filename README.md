# sv128: A Simulated Vector Library

A C++ library for simulating 128-bit vector operations and tracking performance metrics.

## Features

- Simulated 4-wide vector operations for int and float
- C-style API mimicking SIMD instruction sets (sv_int_add, sv_load_int, etc.)
- Masking support for conditional operations
- Built-in performance logger to track vector lane utilization
- Static library format for easy integration

## How to Build

To build the library and test application:

```bash
make
```

This compiles the static library (`libsv128.a`) and the test application (`test_app`).

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

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgements

The prototype for this library is based on the homework assignment code from the Parallel Programming (Fall 2023, pp-23) course taught by Professor Yi-Ping You at NYCU.

This project's structure and code were also bootstrapped with the assistance of AI. Special thanks to the following models for their contributions:

- Google's Gemini 2.5 Pro
- Anthropic's Claude 3 Sonnet via Copilot