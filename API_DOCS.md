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

### sv_logger_get_total_instructions
```cpp
long long sv_logger_get_total_instructions();
```
**Description:** Returns the total number of vector instructions recorded since the last `sv_logger_init()` call.

**Parameters:** None

**Return Value:** The total instruction count as a `long long`.

**Example:**
```cpp
long long instructions = sv_logger_get_total_instructions();
std::cout << "Instructions executed: " << instructions << std::endl;
```

### sv_logger_get_utilized_lanes
```cpp
long long sv_logger_get_utilized_lanes();
```
**Description:** Returns the total number of vector lanes that were active (not masked off) across all recorded instructions since the last `sv_logger_init()` call.

**Parameters:** None

**Return Value:** The total count of utilized lanes as a `long long`.

**Example:**
```cpp
long long active_lanes = sv_logger_get_utilized_lanes();
std::cout << "Active lanes processed: " << active_lanes << std::endl;
```

## Memory & Set Operations

### sv_load_int
```cpp
sv_int4 sv_load_int(sv_int4 passthru, const int* mem_addr, sv_mask mask);
```
**Description:** Loads VECTOR_WIDTH consecutive integers from memory into a vector register. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the passthru vector.

**Parameters:**
- `passthru`: The vector to use for lanes that are masked off
- `mem_addr`: Pointer to the memory location to load from
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the loaded integer values for active lanes and passthru values for inactive lanes

**Example:**
```cpp
int array[4] = {1, 2, 3, 4};
sv_int4 passthru = sv_set_int(10, 20, 30, 40);
sv_mask mask = sv_init_ones(2);  // [T, T, F, F]
sv_int4 vec = sv_load_int(passthru, array, mask);  // [1, 2, 30, 40]
```

### sv_store_int
```cpp
void sv_store_int(int* mem_addr, sv_int4 a, sv_mask mask);
```
**Description:** Stores vector register lanes to consecutive memory locations. The operation is only performed on lanes where the mask is true. Memory locations corresponding to inactive lanes remain unchanged.

**Parameters:**
- `mem_addr`: Pointer to the memory location to store to
- `a`: Vector register to store
- `mask`: Mask controlling which lanes to operate on

**Return Value:** None

**Example:**
```cpp
int result[4] = {10, 20, 30, 40};  // Initial values
sv_mask mask = sv_init_ones(2);    // [T, T, F, F]
sv_store_int(result, vec, mask);   // result becomes [1, 2, 30, 40]
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
sv_int4 sv_set1_int(sv_int4 passthru, int val, sv_mask mask);
```
**Description:** Creates a vector with specified lanes set to the same value. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the passthru vector.

**Parameters:**
- `passthru`: The vector to use for lanes that are masked off
- `val`: Value to broadcast to active lanes
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector with active lanes set to the specified value and inactive lanes from passthru

**Example:**
```cpp
sv_int4 passthru = sv_set_int(1, 2, 3, 4);
sv_mask mask = sv_init_ones(2);  // [T, T, F, F]
sv_int4 vec = sv_set1_int(passthru, 42, mask);  // [42, 42, 3, 4]
```

### sv_load_float
```cpp
sv_float4 sv_load_float(sv_float4 passthru, const float* mem_addr, sv_mask mask);
```
**Description:** Loads VECTOR_WIDTH consecutive floats from memory into a vector register. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the passthru vector.

**Parameters:**
- `passthru`: The vector to use for lanes that are masked off
- `mem_addr`: Pointer to the memory location to load from
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the loaded float values for active lanes and passthru values for inactive lanes

**Example:**
```cpp
float array[4] = {1.5f, 2.5f, 3.5f, 4.5f};
sv_float4 passthru = sv_set_float(10.0f, 20.0f, 30.0f, 40.0f);
sv_mask mask = sv_init_ones(3);  // [T, T, T, F]
sv_float4 vec = sv_load_float(passthru, array, mask);  // [1.5, 2.5, 3.5, 40.0]
```

### sv_store_float
```cpp
void sv_store_float(float* mem_addr, sv_float4 a, sv_mask mask);
```
**Description:** Stores float vector register lanes to consecutive memory locations. The operation is only performed on lanes where the mask is true. Memory locations corresponding to inactive lanes remain unchanged.

**Parameters:**
- `mem_addr`: Pointer to the memory location to store to
- `a`: Vector register to store
- `mask`: Mask controlling which lanes to operate on

**Return Value:** None

**Example:**
```cpp
float result[4] = {10.0f, 20.0f, 30.0f, 40.0f};  // Initial values
sv_mask mask = sv_init_ones(2);                   // [T, T, F, F]
sv_store_float(result, vec, mask);                // result becomes [1.5, 2.5, 30.0, 40.0]
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
sv_float4 sv_set1_float(sv_float4 passthru, float val, sv_mask mask);
```
**Description:** Creates a float vector with specified lanes set to the same value. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the passthru vector.

**Parameters:**
- `passthru`: The vector to use for lanes that are masked off
- `val`: Value to broadcast to active lanes
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector with active lanes set to the specified value and inactive lanes from passthru

**Example:**
```cpp
sv_float4 passthru = sv_set_float(1.0f, 2.0f, 3.0f, 4.0f);
sv_mask mask = sv_init_ones(3);  // [T, T, T, F]
sv_float4 vec = sv_set1_float(passthru, 3.14f, mask);  // [3.14, 3.14, 3.14, 4.0]
```

## Vector Arithmetic

### sv_int_add
```cpp
sv_int4 sv_int_add(sv_int4 a, sv_int4 b, sv_mask mask);
```
**Description:** Performs element-wise addition of two integer vectors. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the first operand (a).

**Parameters:**
- `a`: First vector operand (also provides values for masked-off lanes)
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the element-wise sum for active lanes and values from 'a' for inactive lanes

**Example:**
```cpp
sv_int4 a = sv_set_int(1, 2, 3, 4);
sv_int4 b = sv_set_int(5, 6, 7, 8);
sv_mask mask = sv_init_ones(2);        // [T, T, F, F]
sv_int4 result = sv_int_add(a, b, mask);  // [6, 8, 3, 4]
```

### sv_int_sub
```cpp
sv_int4 sv_int_sub(sv_int4 a, sv_int4 b, sv_mask mask);
```
**Description:** Performs element-wise subtraction of two integer vectors. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the first operand (a).

**Parameters:**
- `a`: First vector operand (also provides values for masked-off lanes)
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the element-wise difference for active lanes and values from 'a' for inactive lanes

**Example:**
```cpp
sv_int4 result = sv_int_sub(b, a, mask);  // [4, 4, 7, 8]
```

### sv_int_mul
```cpp
sv_int4 sv_int_mul(sv_int4 a, sv_int4 b, sv_mask mask);
```
**Description:** Performs element-wise multiplication of two integer vectors. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the first operand (a).

**Parameters:**
- `a`: First vector operand (also provides values for masked-off lanes)
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the element-wise product for active lanes and values from 'a' for inactive lanes

**Example:**
```cpp
sv_int4 result = sv_int_mul(a, b, mask);  // [5, 12, 3, 4]
```

### sv_int_div
```cpp
sv_int4 sv_int_div(sv_int4 a, sv_int4 b, sv_mask mask);
```
**Description:** Performs element-wise division of two integer vectors. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the first operand (a).

**Parameters:**
- `a`: Dividend vector (also provides values for masked-off lanes)
- `b`: Divisor vector
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the element-wise quotient for active lanes and values from 'a' for inactive lanes

**Example:**
```cpp
sv_int4 result = sv_int_div(b, a, mask);  // [5, 3, 7, 8]
```

### sv_int_abs
```cpp
sv_int4 sv_int_abs(sv_int4 a, sv_mask mask);
```
**Description:** Computes the absolute value of each element in an integer vector. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the input vector (a).

**Parameters:**
- `a`: Input vector (also provides values for masked-off lanes)
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the absolute values for active lanes and original values from 'a' for inactive lanes

**Example:**
```cpp
sv_int4 negative = sv_set_int(-1, -2, 3, -4);
sv_mask mask = sv_init_ones(3);  // [T, T, T, F]
sv_int4 result = sv_int_abs(negative, mask);  // [1, 2, 3, -4]
```

### sv_float_add
```cpp
sv_float4 sv_float_add(sv_float4 a, sv_float4 b, sv_mask mask);
```
**Description:** Performs element-wise addition of two float vectors. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the first operand (a).

**Parameters:**
- `a`: First vector operand (also provides values for masked-off lanes)
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the element-wise sum for active lanes and values from 'a' for inactive lanes

**Example:**
```cpp
sv_float4 a = sv_set_float(1.5f, 2.5f, 3.5f, 4.5f);
sv_float4 b = sv_set_float(0.5f, 1.0f, 2.0f, 3.0f);
sv_mask mask = sv_init_ones(3);  // [T, T, T, F]
sv_float4 result = sv_float_add(a, b, mask);  // [2.0, 3.5, 5.5, 4.5]
```

### sv_float_sub
```cpp
sv_float4 sv_float_sub(sv_float4 a, sv_float4 b, sv_mask mask);
```
**Description:** Performs element-wise subtraction of two float vectors. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the first operand (a).

**Parameters:**
- `a`: First vector operand (also provides values for masked-off lanes)
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the element-wise difference for active lanes and values from 'a' for inactive lanes

**Example:**
```cpp
sv_float4 result = sv_float_sub(a, b, mask);  // [1.0, 1.5, 1.5, 4.5]
```

### sv_float_mul
```cpp
sv_float4 sv_float_mul(sv_float4 a, sv_float4 b, sv_mask mask);
```
**Description:** Performs element-wise multiplication of two float vectors. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the first operand (a).

**Parameters:**
- `a`: First vector operand (also provides values for masked-off lanes)
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the element-wise product for active lanes and values from 'a' for inactive lanes

**Example:**
```cpp
sv_float4 result = sv_float_mul(a, b, mask);  // [0.75, 2.5, 7.0, 4.5]
```

### sv_float_div
```cpp
sv_float4 sv_float_div(sv_float4 a, sv_float4 b, sv_mask mask);
```
**Description:** Performs element-wise division of two float vectors. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the first operand (a).

**Parameters:**
- `a`: Dividend vector (also provides values for masked-off lanes)
- `b`: Divisor vector
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the element-wise quotient for active lanes and values from 'a' for inactive lanes

**Example:**
```cpp
sv_float4 result = sv_float_div(a, b, mask);  // [3.0, 2.5, 1.75, 4.5]
```

### sv_float_abs
```cpp
sv_float4 sv_float_abs(sv_float4 a, sv_mask mask);
```
**Description:** Computes the absolute value of each element in a float vector. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the input vector (a).

**Parameters:**
- `a`: Input vector (also provides values for masked-off lanes)
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the absolute values for active lanes and original values from 'a' for inactive lanes

**Example:**
```cpp
sv_float4 negative = sv_set_float(-1.5f, -2.5f, 3.5f, -4.5f);
sv_mask mask = sv_init_ones(3);  // [T, T, T, F]
sv_float4 result = sv_float_abs(negative, mask);  // [1.5, 2.5, 3.5, -4.5]
```

### sv_float_sqrt
```cpp
sv_float4 sv_float_sqrt(sv_float4 a, sv_mask mask);
```
**Description:** Computes the square root of each element in a float vector. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the input vector (a).

**Parameters:**
- `a`: Input vector (also provides values for masked-off lanes)
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the square roots for active lanes and original values from 'a' for inactive lanes

**Example:**
```cpp
sv_float4 squares = sv_set_float(1.0f, 4.0f, 9.0f, 16.0f);
sv_mask mask = sv_init_ones(3);  // [T, T, T, F]
sv_float4 result = sv_float_sqrt(squares, mask);  // [1.0, 2.0, 3.0, 16.0]
```

## Advanced Vector Operations

### sv_int_min
```cpp
sv_int4 sv_int_min(sv_int4 a, sv_int4 b, sv_mask mask);
```
**Description:** Computes the element-wise minimum of two integer vectors. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the first operand (a).

**Parameters:**
- `a`: First vector operand (also provides values for masked-off lanes)
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the element-wise minimum for active lanes and values from 'a' for inactive lanes

**Example:**
```cpp
sv_int4 a = sv_set_int(5, 2, 8, 1);
sv_int4 b = sv_set_int(3, 6, 4, 9);
sv_mask mask = sv_init_ones(3);  // [T, T, T, F]
sv_int4 result = sv_int_min(a, b, mask);  // [3, 2, 4, 1]
```

### sv_int_max
```cpp
sv_int4 sv_int_max(sv_int4 a, sv_int4 b, sv_mask mask);
```
**Description:** Computes the element-wise maximum of two integer vectors. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the first operand (a).

**Parameters:**
- `a`: First vector operand (also provides values for masked-off lanes)
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the element-wise maximum for active lanes and values from 'a' for inactive lanes

**Example:**
```cpp
sv_int4 result = sv_int_max(a, b, mask);  // [5, 6, 8, 1]
```

### sv_float_min
```cpp
sv_float4 sv_float_min(sv_float4 a, sv_float4 b, sv_mask mask);
```
**Description:** Computes the element-wise minimum of two float vectors. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the first operand (a).

**Parameters:**
- `a`: First vector operand (also provides values for masked-off lanes)
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the element-wise minimum for active lanes and values from 'a' for inactive lanes

**Example:**
```cpp
sv_float4 a = sv_set_float(5.5f, 2.1f, 8.3f, 1.7f);
sv_float4 b = sv_set_float(3.2f, 6.8f, 4.1f, 9.5f);
sv_mask mask = sv_init_ones(3);  // [T, T, T, F]
sv_float4 result = sv_float_min(a, b, mask);  // [3.2, 2.1, 4.1, 1.7]
```

### sv_float_max
```cpp
sv_float4 sv_float_max(sv_float4 a, sv_float4 b, sv_mask mask);
```
**Description:** Computes the element-wise maximum of two float vectors. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the first operand (a).

**Parameters:**
- `a`: First vector operand (also provides values for masked-off lanes)
- `b`: Second vector operand
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector containing the element-wise maximum for active lanes and values from 'a' for inactive lanes

**Example:**
```cpp
sv_float4 result = sv_float_max(a, b, mask);  // [5.5, 6.8, 8.3, 1.7]
```

### sv_float_hadd
```cpp
sv_float4 sv_float_hadd(sv_float4 a, sv_mask mask);
```
**Description:** Performs horizontal addition on pairs of adjacent elements. Transforms [a,b,c,d] to [a+b, a+b, c+d, c+d]. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the input vector (a).

**Parameters:**
- `a`: Input vector (also provides values for masked-off lanes)
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector with horizontal sums for active lanes and original values from 'a' for inactive lanes

**Example:**
```cpp
sv_float4 input = sv_set_float(1.0f, 2.0f, 3.0f, 4.0f);
sv_mask mask = sv_init_ones(2);  // [T, T, F, F]
sv_float4 result = sv_float_hadd(input, mask);  // [3.0, 3.0, 3.0, 4.0]
```

### sv_float_interleave
```cpp
sv_float4 sv_float_interleave(sv_float4 a, sv_mask mask);
```
**Description:** Interleaves elements by swapping the middle two elements. Transforms [a,b,c,d] to [a,c,b,d]. The operation is only performed on lanes where the mask is true. For lanes where the mask is false, the result comes from the input vector (a).

**Parameters:**
- `a`: Input vector (also provides values for masked-off lanes)
- `mask`: Mask controlling which lanes to operate on

**Return Value:** Vector with interleaved elements for active lanes and original values from 'a' for inactive lanes

**Example:**
```cpp
sv_float4 input = sv_set_float(1.0f, 2.0f, 3.0f, 4.0f);
sv_mask mask = sv_init_ones(4);  // [T, T, T, T]
sv_float4 result = sv_float_interleave(input, mask);  // [1.0, 3.0, 2.0, 4.0]
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

### sv_int_le
```cpp
sv_mask sv_int_le(sv_int4 a, sv_int4 b);
```
**Description:** Performs element-wise less-than-or-equal comparison between two integer vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Mask indicating which lanes of `a` are less than or equal to `b`

**Example:**
```cpp
sv_int4 a = sv_set_int(1, 2, 3, 4);
sv_int4 b = sv_set_int(1, 0, 3, 5);
sv_mask result = sv_int_le(a, b);  // [T, F, T, T]
```

### sv_int_ge
```cpp
sv_mask sv_int_ge(sv_int4 a, sv_int4 b);
```
**Description:** Performs element-wise greater-than-or-equal comparison between two integer vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Mask indicating which lanes of `a` are greater than or equal to `b`

**Example:**
```cpp
sv_mask result = sv_int_ge(a, b);  // [T, T, T, F]
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

### sv_float_le
```cpp
sv_mask sv_float_le(sv_float4 a, sv_float4 b);
```
**Description:** Performs element-wise less-than-or-equal comparison between two float vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Mask indicating which lanes of `a` are less than or equal to `b`

**Example:**
```cpp
sv_float4 a = sv_set_float(1.0f, 2.0f, 3.0f, 4.0f);
sv_float4 b = sv_set_float(1.0f, 0.0f, 3.0f, 5.0f);
sv_mask result = sv_float_le(a, b);  // [T, F, T, T]
```

### sv_float_ge
```cpp
sv_mask sv_float_ge(sv_float4 a, sv_float4 b);
```
**Description:** Performs element-wise greater-than-or-equal comparison between two float vectors.

**Parameters:**
- `a`: First vector operand
- `b`: Second vector operand

**Return Value:** Mask indicating which lanes of `a` are greater than or equal to `b`

**Example:**
```cpp
sv_mask result = sv_float_ge(a, b);  // [T, T, T, F]
```

## Mask Operations

### sv_mask_all_true
```cpp
sv_mask sv_mask_all_true();
```
**Description:** Creates a mask with all lanes set to true.

**Parameters:** None

**Return Value:** Mask with all lanes set to true

**Example:**
```cpp
sv_mask mask = sv_mask_all_true();  // [T, T, T, T]
```

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

### sv_mask_all
```cpp
bool sv_mask_all(sv_mask a);
```
**Description:** Checks if all lanes in a mask are true.

**Parameters:**
- `a`: Input mask

**Return Value:** True if all lanes are true, false otherwise

**Example:**
```cpp
sv_mask mask1 = sv_mask_all_true();     // [T, T, T, T]
sv_mask mask2 = sv_init_ones(3);        // [T, T, T, F]
bool result1 = sv_mask_all(mask1);      // true
bool result2 = sv_mask_all(mask2);      // false
```

### sv_mask_any
```cpp
bool sv_mask_any(sv_mask a);
```
**Description:** Checks if any lane in a mask is true.

**Parameters:**
- `a`: Input mask

**Return Value:** True if at least one lane is true, false otherwise

**Example:**
```cpp
sv_mask mask1 = sv_init_ones(1);        // [T, F, F, F]
sv_mask mask2 = sv_mask_not(sv_mask_all_true());  // [F, F, F, F]
bool result1 = sv_mask_any(mask1);      // true
bool result2 = sv_mask_any(mask2);      // false
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