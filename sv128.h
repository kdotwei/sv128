#ifndef SV128_H
#define SV128_H

#include <iostream>

#define VECTOR_WIDTH 4

// Mask Type
struct sv_mask {
    bool data[VECTOR_WIDTH];
};

// Integer Vector Type
struct sv_int4 {
    int data[VECTOR_WIDTH];
};

// Float Vector Type
struct sv_float4 {
    float data[VECTOR_WIDTH];
};

// Memory Operations - Integer
sv_int4 sv_load_int(sv_int4 passthru, const int* mem_addr, sv_mask mask);
void sv_store_int(int* mem_addr, sv_int4 a, sv_mask mask);
sv_int4 sv_set_int(int i0, int i1, int i2, int i3);
sv_int4 sv_set1_int(sv_int4 passthru, int val, sv_mask mask);

// Memory Operations - Float
sv_float4 sv_load_float(sv_float4 passthru, const float* mem_addr, sv_mask mask);
void sv_store_float(float* mem_addr, sv_float4 a, sv_mask mask);
sv_float4 sv_set_float(float f0, float f1, float f2, float f3);
sv_float4 sv_set1_float(sv_float4 passthru, float val, sv_mask mask);

// Arithmetic Operations - Integer
sv_int4 sv_int_add(sv_int4 a, sv_int4 b, sv_mask mask);
sv_int4 sv_int_sub(sv_int4 a, sv_int4 b, sv_mask mask);
sv_int4 sv_int_mul(sv_int4 a, sv_int4 b, sv_mask mask);
sv_int4 sv_int_div(sv_int4 a, sv_int4 b, sv_mask mask);

// Arithmetic Operations - Float
sv_float4 sv_float_add(sv_float4 a, sv_float4 b, sv_mask mask);
sv_float4 sv_float_sub(sv_float4 a, sv_float4 b, sv_mask mask);
sv_float4 sv_float_mul(sv_float4 a, sv_float4 b, sv_mask mask);
sv_float4 sv_float_div(sv_float4 a, sv_float4 b, sv_mask mask);

// Advanced Operations - Integer
sv_int4 sv_int_min(sv_int4 a, sv_int4 b, sv_mask mask);
sv_int4 sv_int_max(sv_int4 a, sv_int4 b, sv_mask mask);
sv_int4 sv_int_abs(sv_int4 a, sv_mask mask);

// Advanced Operations - Float
sv_float4 sv_float_min(sv_float4 a, sv_float4 b, sv_mask mask);
sv_float4 sv_float_max(sv_float4 a, sv_float4 b, sv_mask mask);
sv_float4 sv_float_abs(sv_float4 a, sv_mask mask);
sv_float4 sv_float_sqrt(sv_float4 a, sv_mask mask);
sv_float4 sv_float_hadd(sv_float4 a, sv_mask mask);
sv_float4 sv_float_interleave(sv_float4 a, sv_mask mask);

// Comparison Operations - Integer
sv_mask sv_int_eq(sv_int4 a, sv_int4 b, sv_mask mask);
sv_mask sv_int_lt(sv_int4 a, sv_int4 b, sv_mask mask);
sv_mask sv_int_le(sv_int4 a, sv_int4 b, sv_mask mask);
sv_mask sv_int_gt(sv_int4 a, sv_int4 b, sv_mask mask);
sv_mask sv_int_ge(sv_int4 a, sv_int4 b, sv_mask mask);

// Comparison Operations - Float
sv_mask sv_float_eq(sv_float4 a, sv_float4 b, sv_mask mask);
sv_mask sv_float_lt(sv_float4 a, sv_float4 b, sv_mask mask);
sv_mask sv_float_le(sv_float4 a, sv_float4 b, sv_mask mask);
sv_mask sv_float_gt(sv_float4 a, sv_float4 b, sv_mask mask);
sv_mask sv_float_ge(sv_float4 a, sv_float4 b, sv_mask mask);

// Mask Operations
sv_mask sv_mask_all_true();
sv_mask sv_init_ones(int first_n);
sv_mask sv_mask_and(sv_mask a, sv_mask b);
sv_mask sv_mask_or(sv_mask a, sv_mask b);
sv_mask sv_mask_not(sv_mask a);
bool sv_mask_all(sv_mask a);
bool sv_mask_any(sv_mask a);
int sv_cntbits(sv_mask a);

// Utility Functions
std::ostream& operator<<(std::ostream& os, const sv_int4& v);
std::ostream& operator<<(std::ostream& os, const sv_float4& v);
std::ostream& operator<<(std::ostream& os, const sv_mask& m);

#endif // SV128_H