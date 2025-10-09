# sv128 Library API Documentation

This document provides detailed documentation for all public functions in the sv128 simulated vector library.

## Data Types

### sv_mask
```cpp
struct sv_mask {
    bool data[VECTOR_WIDTH];
};
```
A vector mask with VECTOR_WIDTH boolean lanes used for conditional operations. Each lane can be either `true` or `false`, controlling which vector lanes participate in masked operations.

### sv_int4
```cpp
struct sv_int4 {
    int data[VECTOR_WIDTH];
};
```
A vector register containing VECTOR_WIDTH integer values. Used for integer vector operations.

### sv_float4
```cpp
struct sv_float4 {
    float data[VECTOR_WIDTH];
};
```
A vector register containing VECTOR_WIDTH floating-point values. Used for float vector operations.

## Logger Functions

### sv_logger_init
```cpp
void sv_logger_init();
```
**Description:** Resets all performance counters to zero.

**Parameters:** None

**Return Value:** None

**Example:**
```cpp
sv_logger_init();  // Reset performance counters
```

### sv_logger_print_stats
```cpp
void sv_logger_print_stats();
```
**Description:** Prints a summary of collected performance statistics including total instructions, utilized lanes, and lane utilization rate.

**Parameters:** None

**Return Value:** None

**Example:**
```cpp
sv_logger_print_stats();  // Display performance summary
```

## Memory & Set Operations

### sv_load_int
```cpp
sv_int4 sv_load_int(const int* mem_addr);
```
**Description:** Loads VECTOR_WIDTH consecutive integers from memory into a vector register.

**Parameters:**
- `mem_addr`: Pointer to the memory location to load from

**Return Value:** Vector containing the loaded integer values

**Example:**
```cpp
int array[4] = {1, 2, 3, 4};
sv_int4 vec = sv_load_int(array);
```

### sv_store_int
```cpp
void sv_store_int(int* mem_addr, sv_int4 a);
```
**Description:** Stores all lanes of a vector register to consecutive memory locations.

**Parameters:**
- `mem_addr`: Pointer to the memory location to store to
- `a`: Vector register to store

**Return Value:** None

**Example:**
```cpp
int result[4];
sv_store_int(result, vec);
```

### sv_set_int
```cpp
sv_int4 sv_set_int(int i0, int i1, int i2, int i3);
```
**Description:** Creates a vector with explicitly provided values for each lane.

**Parameters:**
- `i0`, `i1`, `i2`, `i3`: Values for each vector lane

**Return Value:** Vector with the specified values

**Example:**
```cpp
sv_int4 vec = sv_set_int(10, 20, 30, 40);
```

### sv_set1_int
```cpp
sv_int4 sv_set1_int(int val);
```
**Description:** Creates a vector with all lanes set to the same value.

**Parameters:**
- `val`: Value to broadcast to all lanes

**Return Value:** Vector with all lanes set to the specified value

**Example:**
```cpp
sv_int4 vec = sv_set1_int(42);  // [42, 42, 42, 42]
```

### sv_load_float
```cpp
sv_float4 sv_load_float(const float* mem_addr);
```
**Description:** Loads VECTOR_WIDTH consecutive floats from memory into a vector register.

**Parameters:**
- `mem_addr`: Pointer to the memory location to load from

**Return Value:** Vector containing the loaded float values

**Example:**
```cpp
float array[4] = {1.5f, 2.5f, 3.5f, 4.5f};
sv_float4 vec = sv_load_float(array);
```

### sv_store_float
```cpp
void sv_store_float(float* mem_addr, sv_float4 a);
```
**Description:** Stores all lanes of a float vector register to consecutive memory locations.

**Parameters:**
- `mem_addr`: Pointer to the memory location to store to
- `a`: Vector register to store

**Return Value:** None

**Example:**
```cpp
float result[4];
sv_store_float(result, vec);
```

### sv_set_float
```cpp
sv_float4 sv_set_float(float f0, float f1, float f2, float f3);
```
**Description:** Creates a float vector with explicitly provided values for each lane.

**Parameters:**
- `f0`, `f1`, `f2`, `f3`: Values for each vector lane

**Return Value:** Vector with the specified values

**Example:**
```cpp
sv_float4 vec = sv_set_float(1.0f, 2.0f, 3.0f, 4.0f);
```

### sv_set1_float
```cpp
sv_float4 sv_set1_float(float val);
```
**Description:** Creates a float vector with all lanes set to the same value.

**Parameters:**
- `val`: Value to broadcast to all lanes

**Return Value:** Vector with all lanes set to the specified value

**Example:**
```cpp
sv_float4 vec = sv_set1_float(3.14f);  // [3.14, 3.14, 3.14, 3.14]
```

## Vector Arithmetic

### sv_int_add
```cpp
sv_int4 sv_int_add(sv_int4 a, sv_int4 b);
```
**Description:** Performs element-wise addition of two integer vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Vector containing the element-wise sum

**Example:**
```cpp
sv_int4 a = sv_set_int(1, 2, 3, 4);
sv_int4 b = sv_set_int(5, 6, 7, 8);
sv_int4 result = sv_int_add(a, b);  // [6, 8, 10, 12]
```

### sv_int_sub
```cpp
sv_int4 sv_int_sub(sv_int4 a, sv_int4 b);
```
**Description:** Performs element-wise subtraction of two integer vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Vector containing the element-wise difference

**Example:**
```cpp
sv_int4 result = sv_int_sub(b, a);  // [4, 4, 4, 4]
```

### sv_int_mul
```cpp
sv_int4 sv_int_mul(sv_int4 a, sv_int4 b);
```
**Description:** Performs element-wise multiplication of two integer vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Vector containing the element-wise product

**Example:**
```cpp
sv_int4 result = sv_int_mul(a, b);  // [5, 12, 21, 32]
```

### sv_int_div
```cpp
sv_int4 sv_int_div(sv_int4 a, sv_int4 b);
```
**Description:** Performs element-wise division of two integer vectors.

**Parameters:**
- `a`: Dividend vector
- `b`: Divisor vector

**Return Value:** Vector containing the element-wise quotient

**Example:**
```cpp
sv_int4 result = sv_int_div(b, a);  // [5, 3, 2, 2]
```

### sv_int_abs
```cpp
sv_int4 sv_int_abs(sv_int4 a);
```
**Description:** Computes the absolute value of each element in an integer vector.

**Parameters:**
- `a`: Input vector

**Return Value:** Vector containing the absolute values

**Example:**
```cpp
sv_int4 negative = sv_set_int(-1, -2, 3, -4);
sv_int4 result = sv_int_abs(negative);  // [1, 2, 3, 4]
```

### sv_float_add
```cpp
sv_float4 sv_float_add(sv_float4 a, sv_float4 b);
```
**Description:** Performs element-wise addition of two float vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Vector containing the element-wise sum

**Example:**
```cpp
sv_float4 a = sv_set_float(1.5f, 2.5f, 3.5f, 4.5f);
sv_float4 b = sv_set_float(0.5f, 1.0f, 2.0f, 3.0f);
sv_float4 result = sv_float_add(a, b);  // [2.0, 3.5, 5.5, 7.5]
```

### sv_float_sub
```cpp
sv_float4 sv_float_sub(sv_float4 a, sv_float4 b);
```
**Description:** Performs element-wise subtraction of two float vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Vector containing the element-wise difference

**Example:**
```cpp
sv_float4 result = sv_float_sub(a, b);  // [1.0, 1.5, 1.5, 1.5]
```

### sv_float_mul
```cpp
sv_float4 sv_float_mul(sv_float4 a, sv_float4 b);
```
**Description:** Performs element-wise multiplication of two float vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Vector containing the element-wise product

**Example:**
```cpp
sv_float4 result = sv_float_mul(a, b);  // [0.75, 2.5, 7.0, 13.5]
```

### sv_float_div
```cpp
sv_float4 sv_float_div(sv_float4 a, sv_float4 b);
```
**Description:** Performs element-wise division of two float vectors.

**Parameters:**
- `a`: Dividend vector
- `b`: Divisor vector

**Return Value:** Vector containing the element-wise quotient

**Example:**
```cpp
sv_float4 result = sv_float_div(a, b);  // [3.0, 2.5, 1.75, 1.5]
```

### sv_float_abs
```cpp
sv_float4 sv_float_abs(sv_float4 a);
```
**Description:** Computes the absolute value of each element in a float vector.

**Parameters:**
- `a`: Input vector

**Return Value:** Vector containing the absolute values

**Example:**
```cpp
sv_float4 negative = sv_set_float(-1.5f, -2.5f, 3.5f, -4.5f);
sv_float4 result = sv_float_abs(negative);  // [1.5, 2.5, 3.5, 4.5]
```

### sv_float_sqrt
```cpp
sv_float4 sv_float_sqrt(sv_float4 a);
```
**Description:** Computes the square root of each element in a float vector.

**Parameters:**
- `a`: Input vector

**Return Value:** Vector containing the square roots

**Example:**
```cpp
sv_float4 squares = sv_set_float(1.0f, 4.0f, 9.0f, 16.0f);
sv_float4 result = sv_float_sqrt(squares);  // [1.0, 2.0, 3.0, 4.0]
```

## Advanced Vector Operations

### sv_float_hadd
```cpp
sv_float4 sv_float_hadd(sv_float4 a);
```
**Description:** Performs horizontal addition on pairs of adjacent elements. Transforms [a,b,c,d] to [a+b, a+b, c+d, c+d].

**Parameters:**
- `a`: Input vector

**Return Value:** Vector with horizontal sums

**Example:**
```cpp
sv_float4 input = sv_set_float(1.0f, 2.0f, 3.0f, 4.0f);
sv_float4 result = sv_float_hadd(input);  // [3.0, 3.0, 7.0, 7.0]
```

### sv_float_interleave
```cpp
sv_float4 sv_float_interleave(sv_float4 a);
```
**Description:** Interleaves elements by swapping the middle two elements. Transforms [a,b,c,d] to [a,c,b,d].

**Parameters:**
- `a`: Input vector

**Return Value:** Vector with interleaved elements

**Example:**
```cpp
sv_float4 input = sv_set_float(1.0f, 2.0f, 3.0f, 4.0f);
sv_float4 result = sv_float_interleave(input);  // [1.0, 3.0, 2.0, 4.0]
```

## Vector Comparison

### sv_int_eq
```cpp
sv_mask sv_int_eq(sv_int4 a, sv_int4 b);
```
**Description:** Performs element-wise equality comparison between two integer vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Mask indicating which lanes are equal

**Example:**
```cpp
sv_int4 a = sv_set_int(1, 2, 3, 4);
sv_int4 b = sv_set_int(1, 0, 3, 5);
sv_mask result = sv_int_eq(a, b);  // [T, F, T, F]
```

### sv_int_lt
```cpp
sv_mask sv_int_lt(sv_int4 a, sv_int4 b);
```
**Description:** Performs element-wise less-than comparison between two integer vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Mask indicating which lanes of `a` are less than `b`

**Example:**
```cpp
sv_mask result = sv_int_lt(a, b);  // [F, F, F, T]
```

### sv_int_gt
```cpp
sv_mask sv_int_gt(sv_int4 a, sv_int4 b);
```
**Description:** Performs element-wise greater-than comparison between two integer vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Mask indicating which lanes of `a` are greater than `b`

**Example:**
```cpp
sv_mask result = sv_int_gt(a, b);  // [F, T, F, F]
```

### sv_float_eq
```cpp
sv_mask sv_float_eq(sv_float4 a, sv_float4 b);
```
**Description:** Performs element-wise equality comparison between two float vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Mask indicating which lanes are equal

**Example:**
```cpp
sv_float4 a = sv_set_float(1.0f, 2.0f, 3.0f, 4.0f);
sv_float4 b = sv_set_float(1.0f, 0.0f, 3.0f, 5.0f);
sv_mask result = sv_float_eq(a, b);  // [T, F, T, F]
```

### sv_float_lt
```cpp
sv_mask sv_float_lt(sv_float4 a, sv_float4 b);
```
**Description:** Performs element-wise less-than comparison between two float vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Mask indicating which lanes of `a` are less than `b`

**Example:**
```cpp
sv_mask result = sv_float_lt(a, b);  // [F, F, F, T]
```

### sv_float_gt
```cpp
sv_mask sv_float_gt(sv_float4 a, sv_float4 b);
```
**Description:** Performs element-wise greater-than comparison between two float vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Mask indicating which lanes of `a` are greater than `b`

**Example:**
```cpp
sv_mask result = sv_float_gt(a, b);  // [F, T, F, F]
```

## Mask Operations

### sv_init_ones
```cpp
sv_mask sv_init_ones(int first_n);
```
**Description:** Creates a mask with the first `n` lanes set to true and the remaining lanes set to false.

**Parameters:**
- `first_n`: Number of lanes to set to true (from the beginning)

**Return Value:** Mask with the specified pattern

**Example:**
```cpp
sv_mask mask = sv_init_ones(2);  // [T, T, F, F]
```

### sv_mask_not
```cpp
sv_mask sv_mask_not(sv_mask a);
```
**Description:** Performs logical NOT operation on each lane of a mask.

**Parameters:**
- `a`: Input mask

**Return Value:** Mask with inverted values

**Example:**
```cpp
sv_mask input = sv_init_ones(2);     // [T, T, F, F]
sv_mask result = sv_mask_not(input); // [F, F, T, T]
```

### sv_mask_or
```cpp
sv_mask sv_mask_or(sv_mask a, sv_mask b);
```
**Description:** Performs element-wise logical OR operation on two masks.

**Parameters:**
- `a`: First mask operand
- `b`: Second mask operand

**Return Value:** Mask containing the OR results

**Example:**
```cpp
sv_mask a = sv_init_ones(2);         // [T, T, F, F]
sv_mask b = sv_init_ones(3);         // [T, T, T, F]
sv_mask result = sv_mask_or(a, b);   // [T, T, T, F]
```

### sv_mask_and
```cpp
sv_mask sv_mask_and(sv_mask a, sv_mask b);
```
**Description:** Performs element-wise logical AND operation on two masks.

**Parameters:**
- `a`: First mask operand
- `b`: Second mask operand

**Return Value:** Mask containing the AND results

**Example:**
```cpp
sv_mask result = sv_mask_and(a, b);  // [T, T, F, F]
```

### sv_cntbits
```cpp
int sv_cntbits(sv_mask a);
```
**Description:** Counts the number of true lanes in a mask.

**Parameters:**
- `a`: Input mask

**Return Value:** Number of true lanes

**Example:**
```cpp
sv_mask mask = sv_init_ones(3);      // [T, T, T, F]
int count = sv_cntbits(mask);        // 3
```

## Masked Arithmetic

### sv_int_masked_add
```cpp
sv_int4 sv_int_masked_add(sv_int4 a, sv_int4 b, sv_mask mask);
```
**Description:** Performs addition only on lanes where the mask is true. Other lanes retain their original values from vector `a`.

**Parameters:**
- `a`: First vector operand (also provides values for masked-off lanes)
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector with selective addition applied

**Example:**
```cpp
sv_int4 a = sv_set_int(1, 2, 3, 4);
sv_int4 b = sv_set_int(10, 20, 30, 40);
sv_mask mask = sv_init_ones(2);      // [T, T, F, F]
sv_int4 result = sv_int_masked_add(a, b, mask);  // [11, 22, 3, 4]
```

### sv_int_masked_sub
```cpp
sv_int4 sv_int_masked_sub(sv_int4 a, sv_int4 b, sv_mask mask);
```
**Description:** Performs subtraction only on lanes where the mask is true.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector with selective subtraction applied

**Example:**
```cpp
sv_int4 result = sv_int_masked_sub(b, a, mask);  // [9, 18, 30, 40]
```

### sv_int_masked_mul
```cpp
sv_int4 sv_int_masked_mul(sv_int4 a, sv_int4 b, sv_mask mask);
```
**Description:** Performs multiplication only on lanes where the mask is true.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector with selective multiplication applied

**Example:**
```cpp
sv_int4 result = sv_int_masked_mul(a, b, mask);  // [10, 40, 3, 4]
```

### sv_float_masked_add
```cpp
sv_float4 sv_float_masked_add(sv_float4 a, sv_float4 b, sv_mask mask);
```
**Description:** Performs addition only on float lanes where the mask is true.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector with selective addition applied

**Example:**
```cpp
sv_float4 a = sv_set_float(1.0f, 2.0f, 3.0f, 4.0f);
sv_float4 b = sv_set_float(0.5f, 1.5f, 2.5f, 3.5f);
sv_mask mask = sv_init_ones(3);      // [T, T, T, F]
sv_float4 result = sv_float_masked_add(a, b, mask);  // [1.5, 3.5, 5.5, 4.0]
```

### sv_float_masked_sub
```cpp
sv_float4 sv_float_masked_sub(sv_float4 a, sv_float4 b, sv_mask mask);
```
**Description:** Performs subtraction only on float lanes where the mask is true.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector with selective subtraction applied

**Example:**
```cpp
sv_float4 result = sv_float_masked_sub(a, b, mask);  // [0.5, 0.5, 0.5, 4.0]
```

### sv_float_masked_mul
```cpp
sv_float4 sv_float_masked_mul(sv_float4 a, sv_float4 b, sv_mask mask);
```
**Description:** Performs multiplication only on float lanes where the mask is true.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector with selective multiplication applied

**Example:**
```cpp
sv_float4 result = sv_float_masked_mul(a, b, mask);  // [0.5, 3.0, 7.5, 4.0]
```

## Utility Functions

### operator<< for sv_int4
```cpp
std::ostream& operator<<(std::ostream& os, const sv_int4& v);
```
**Description:** Stream insertion operator for printing integer vectors in a readable format.

**Example:**
```cpp
sv_int4 vec = sv_set_int(1, 2, 3, 4);
std::cout << vec;  // Output: [1, 2, 3, 4]
```

### operator<< for sv_float4
```cpp
std::ostream& operator<<(std::ostream& os, const sv_float4& v);
```
**Description:** Stream insertion operator for printing float vectors in a readable format.

**Example:**
```cpp
sv_float4 vec = sv_set_float(1.5f, 2.5f, 3.5f, 4.5f);
std::cout << vec;  // Output: [1.5, 2.5, 3.5, 4.5]
```

### operator<< for sv_mask
```cpp
std::ostream& operator<<(std::ostream& os, const sv_mask& m);
```
**Description:** Stream insertion operator for printing masks in a readable format using T/F notation.

**Example:**
```cpp
sv_mask mask = sv_init_ones(2);
std::cout << mask;  // Output: [T, T, F, F]
```