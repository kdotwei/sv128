#ifndef SV128_H
#define SV128_H

#include <iostream>

// Conditional includes and vector width definition
#ifdef _AVX_
    #include <immintrin.h>
    #define VECTOR_WIDTH 8
#elif defined(_SSE_)
    #include <immintrin.h>
    #define VECTOR_WIDTH 4
#else
    #define VECTOR_WIDTH 4
#endif

// Mask Type - always uses array regardless of implementation
struct sv_mask {
    bool data[VECTOR_WIDTH];
};

// Vector Types with conditional intrinsic support
#ifdef _AVX_
    // AVX implementation - 8-wide vectors
    struct sv_int8 {
        union {
            int data[8];
            __m256i avx_data;
        };
    };
    
    struct sv_float8 {
        union {
            float data[8];
            __m256 avx_data;
        };
    };
    
    // Type aliases for compatibility
    typedef sv_int8 sv_int4;
    typedef sv_float8 sv_float4;
    
#elif defined(_SSE_)
    // SSE implementation - 4-wide vectors
    struct sv_int4 {
        union {
            int data[4];
            __m128i sse_data;
        };
    };
    
    struct sv_float4 {
        union {
            float data[4];
            __m128 sse_data;
        };
    };
    
#else
    // Scalar implementation - 4-wide vectors
    struct sv_int4 {
        int data[4];
    };
    
    struct sv_float4 {
        float data[4];
    };
#endif

// Memory Operations - Integer
sv_int4 sv_load_int(const int* mem_addr);
void sv_store_int(int* mem_addr, sv_int4 a);
#ifdef _AVX_
sv_int4 sv_set_int(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7);
#else
sv_int4 sv_set_int(int i0, int i1, int i2, int i3);
#endif
sv_int4 sv_set1_int(int val);

// Memory Operations - Float
sv_float4 sv_load_float(const float* mem_addr);
void sv_store_float(float* mem_addr, sv_float4 a);
#ifdef _AVX_
sv_float4 sv_set_float(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7);
#else
sv_float4 sv_set_float(float f0, float f1, float f2, float f3);
#endif
sv_float4 sv_set1_float(float val);

// Arithmetic Operations - Integer
sv_int4 sv_int_add(sv_int4 a, sv_int4 b);
sv_int4 sv_int_sub(sv_int4 a, sv_int4 b);
sv_int4 sv_int_mul(sv_int4 a, sv_int4 b);
sv_int4 sv_int_div(sv_int4 a, sv_int4 b);

// Arithmetic Operations - Float
sv_float4 sv_float_add(sv_float4 a, sv_float4 b);
sv_float4 sv_float_sub(sv_float4 a, sv_float4 b);
sv_float4 sv_float_mul(sv_float4 a, sv_float4 b);
sv_float4 sv_float_div(sv_float4 a, sv_float4 b);

// Advanced Operations - Integer
sv_int4 sv_int_min(sv_int4 a, sv_int4 b);
sv_int4 sv_int_max(sv_int4 a, sv_int4 b);
sv_int4 sv_int_abs(sv_int4 a);

// Advanced Operations - Float
sv_float4 sv_float_min(sv_float4 a, sv_float4 b);
sv_float4 sv_float_max(sv_float4 a, sv_float4 b);
sv_float4 sv_float_abs(sv_float4 a);
sv_float4 sv_float_sqrt(sv_float4 a);
sv_float4 sv_float_hadd(sv_float4 a);
sv_float4 sv_float_interleave(sv_float4 a);

// Comparison Operations - Integer
sv_mask sv_int_eq(sv_int4 a, sv_int4 b);
sv_mask sv_int_lt(sv_int4 a, sv_int4 b);
sv_mask sv_int_le(sv_int4 a, sv_int4 b);
sv_mask sv_int_gt(sv_int4 a, sv_int4 b);
sv_mask sv_int_ge(sv_int4 a, sv_int4 b);

// Comparison Operations - Float
sv_mask sv_float_eq(sv_float4 a, sv_float4 b);
sv_mask sv_float_lt(sv_float4 a, sv_float4 b);
sv_mask sv_float_le(sv_float4 a, sv_float4 b);
sv_mask sv_float_gt(sv_float4 a, sv_float4 b);
sv_mask sv_float_ge(sv_float4 a, sv_float4 b);

// Mask Operations
sv_mask sv_init_ones(int first_n);
sv_mask sv_mask_and(sv_mask a, sv_mask b);
sv_mask sv_mask_or(sv_mask a, sv_mask b);
sv_mask sv_mask_not(sv_mask a);
bool sv_mask_all(sv_mask a);
bool sv_mask_any(sv_mask a);
int sv_cntbits(sv_mask a);

// Masked Arithmetic Operations - Integer
sv_int4 sv_int_masked_add(sv_int4 a, sv_int4 b, sv_mask mask);
sv_int4 sv_int_masked_sub(sv_int4 a, sv_int4 b, sv_mask mask);
sv_int4 sv_int_masked_mul(sv_int4 a, sv_int4 b, sv_mask mask);
sv_int4 sv_int_masked_div(sv_int4 a, sv_int4 b, sv_mask mask);

// Masked Arithmetic Operations - Float
sv_float4 sv_float_masked_add(sv_float4 a, sv_float4 b, sv_mask mask);
sv_float4 sv_float_masked_sub(sv_float4 a, sv_float4 b, sv_mask mask);
sv_float4 sv_float_masked_mul(sv_float4 a, sv_float4 b, sv_mask mask);
sv_float4 sv_float_masked_div(sv_float4 a, sv_float4 b, sv_mask mask);

// Utility Functions
std::ostream& operator<<(std::ostream& os, const sv_int4& v);
std::ostream& operator<<(std::ostream& os, const sv_float4& v);
std::ostream& operator<<(std::ostream& os, const sv_mask& m);

#endif // SV128_H