#include "sv128.h"
#include "sv_logger.h"
#include <immintrin.h>
#include <cmath>

// Memory Operations - Integer
sv_int4 sv_load_int(const int* mem_addr) {
    sv_logger_record_unmasked_op();
    sv_int4 result;
    result.avx_data = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(mem_addr));
    return result;
}

void sv_store_int(int* mem_addr, sv_int4 a) {
    sv_logger_record_unmasked_op();
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(mem_addr), a.avx_data);
}

sv_int4 sv_set_int(int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7) {
    sv_logger_record_unmasked_op();
    sv_int4 result;
    result.avx_data = _mm256_set_epi32(i7, i6, i5, i4, i3, i2, i1, i0);
    return result;
}

sv_int4 sv_set1_int(int val) {
    sv_logger_record_unmasked_op();
    sv_int4 result;
    result.avx_data = _mm256_set1_epi32(val);
    return result;
}

// Memory Operations - Float
sv_float4 sv_load_float(const float* mem_addr) {
    sv_logger_record_unmasked_op();
    sv_float4 result;
    result.avx_data = _mm256_loadu_ps(mem_addr);
    return result;
}

void sv_store_float(float* mem_addr, sv_float4 a) {
    sv_logger_record_unmasked_op();
    _mm256_storeu_ps(mem_addr, a.avx_data);
}

sv_float4 sv_set_float(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7) {
    sv_logger_record_unmasked_op();
    sv_float4 result;
    result.avx_data = _mm256_set_ps(f7, f6, f5, f4, f3, f2, f1, f0);
    return result;
}

sv_float4 sv_set1_float(float val) {
    sv_logger_record_unmasked_op();
    sv_float4 result;
    result.avx_data = _mm256_set1_ps(val);
    return result;
}

// Arithmetic Operations - Integer
sv_int4 sv_int_add(sv_int4 a, sv_int4 b) {
    sv_logger_record_unmasked_op();
    sv_int4 result;
    result.avx_data = _mm256_add_epi32(a.avx_data, b.avx_data);
    return result;
}

sv_int4 sv_int_sub(sv_int4 a, sv_int4 b) {
    sv_logger_record_unmasked_op();
    sv_int4 result;
    result.avx_data = _mm256_sub_epi32(a.avx_data, b.avx_data);
    return result;
}

sv_int4 sv_int_mul(sv_int4 a, sv_int4 b) {
    sv_logger_record_unmasked_op();
    sv_int4 result;
    result.avx_data = _mm256_mullo_epi32(a.avx_data, b.avx_data);
    return result;
}

sv_int4 sv_int_div(sv_int4 a, sv_int4 b) {
    sv_logger_record_unmasked_op();
    sv_int4 result;
    // No direct AVX integer division, fall back to scalar
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = a.data[i] / b.data[i];
    }
    return result;
}

// Arithmetic Operations - Float
sv_float4 sv_float_add(sv_float4 a, sv_float4 b) {
    sv_logger_record_unmasked_op();
    sv_float4 result;
    result.avx_data = _mm256_add_ps(a.avx_data, b.avx_data);
    return result;
}

sv_float4 sv_float_sub(sv_float4 a, sv_float4 b) {
    sv_logger_record_unmasked_op();
    sv_float4 result;
    result.avx_data = _mm256_sub_ps(a.avx_data, b.avx_data);
    return result;
}

sv_float4 sv_float_mul(sv_float4 a, sv_float4 b) {
    sv_logger_record_unmasked_op();
    sv_float4 result;
    result.avx_data = _mm256_mul_ps(a.avx_data, b.avx_data);
    return result;
}

sv_float4 sv_float_div(sv_float4 a, sv_float4 b) {
    sv_logger_record_unmasked_op();
    sv_float4 result;
    result.avx_data = _mm256_div_ps(a.avx_data, b.avx_data);
    return result;
}

// Advanced Operations - Integer
sv_int4 sv_int_min(sv_int4 a, sv_int4 b) {
    sv_logger_record_unmasked_op();
    sv_int4 result;
    result.avx_data = _mm256_min_epi32(a.avx_data, b.avx_data);
    return result;
}

sv_int4 sv_int_max(sv_int4 a, sv_int4 b) {
    sv_logger_record_unmasked_op();
    sv_int4 result;
    result.avx_data = _mm256_max_epi32(a.avx_data, b.avx_data);
    return result;
}

sv_int4 sv_int_abs(sv_int4 a) {
    sv_logger_record_unmasked_op();
    sv_int4 result;
    result.avx_data = _mm256_abs_epi32(a.avx_data);
    return result;
}

// Advanced Operations - Float
sv_float4 sv_float_min(sv_float4 a, sv_float4 b) {
    sv_logger_record_unmasked_op();
    sv_float4 result;
    result.avx_data = _mm256_min_ps(a.avx_data, b.avx_data);
    return result;
}

sv_float4 sv_float_max(sv_float4 a, sv_float4 b) {
    sv_logger_record_unmasked_op();
    sv_float4 result;
    result.avx_data = _mm256_max_ps(a.avx_data, b.avx_data);
    return result;
}

sv_float4 sv_float_abs(sv_float4 a) {
    sv_logger_record_unmasked_op();
    sv_float4 result;
    // Create mask to clear sign bit
    __m256 mask = _mm256_castsi256_ps(_mm256_set1_epi32(0x7FFFFFFF));
    result.avx_data = _mm256_and_ps(a.avx_data, mask);
    return result;
}

sv_float4 sv_float_sqrt(sv_float4 a) {
    sv_logger_record_unmasked_op();
    sv_float4 result;
    result.avx_data = _mm256_sqrt_ps(a.avx_data);
    return result;
}

sv_float4 sv_float_hadd(sv_float4 a) {
    sv_logger_record_unmasked_op();
    sv_float4 result;
    result.avx_data = _mm256_hadd_ps(a.avx_data, a.avx_data);
    return result;
}

sv_float4 sv_float_interleave(sv_float4 a) {
    sv_logger_record_unmasked_op();
    sv_float4 result;
    // [a,b,c,d,e,f,g,h] -> [a,c,b,d,e,g,f,h]
    result.avx_data = _mm256_shuffle_ps(a.avx_data, a.avx_data, _MM_SHUFFLE(3, 1, 2, 0));
    return result;
}

// Comparison Operations - Integer
sv_mask sv_int_eq(sv_int4 a, sv_int4 b) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    __m256i cmp = _mm256_cmpeq_epi32(a.avx_data, b.avx_data);
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = (((int*)&cmp)[i] != 0);
    }
    return result;
}

sv_mask sv_int_lt(sv_int4 a, sv_int4 b) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    __m256i cmp = _mm256_cmpgt_epi32(b.avx_data, a.avx_data); // b > a means a < b
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = (((int*)&cmp)[i] != 0);
    }
    return result;
}

sv_mask sv_int_le(sv_int4 a, sv_int4 b) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    __m256i cmp = _mm256_or_si256(_mm256_cmpgt_epi32(b.avx_data, a.avx_data), 
                                  _mm256_cmpeq_epi32(a.avx_data, b.avx_data));
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = (((int*)&cmp)[i] != 0);
    }
    return result;
}

sv_mask sv_int_gt(sv_int4 a, sv_int4 b) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    __m256i cmp = _mm256_cmpgt_epi32(a.avx_data, b.avx_data);
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = (((int*)&cmp)[i] != 0);
    }
    return result;
}

sv_mask sv_int_ge(sv_int4 a, sv_int4 b) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    __m256i cmp = _mm256_or_si256(_mm256_cmpgt_epi32(a.avx_data, b.avx_data), 
                                  _mm256_cmpeq_epi32(a.avx_data, b.avx_data));
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = (((int*)&cmp)[i] != 0);
    }
    return result;
}

// Comparison Operations - Float
sv_mask sv_float_eq(sv_float4 a, sv_float4 b) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    __m256 cmp = _mm256_cmp_ps(a.avx_data, b.avx_data, _CMP_EQ_OQ);
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = (((int*)&cmp)[i] != 0);
    }
    return result;
}

sv_mask sv_float_lt(sv_float4 a, sv_float4 b) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    __m256 cmp = _mm256_cmp_ps(a.avx_data, b.avx_data, _CMP_LT_OQ);
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = (((int*)&cmp)[i] != 0);
    }
    return result;
}

sv_mask sv_float_le(sv_float4 a, sv_float4 b) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    __m256 cmp = _mm256_cmp_ps(a.avx_data, b.avx_data, _CMP_LE_OQ);
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = (((int*)&cmp)[i] != 0);
    }
    return result;
}

sv_mask sv_float_gt(sv_float4 a, sv_float4 b) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    __m256 cmp = _mm256_cmp_ps(a.avx_data, b.avx_data, _CMP_GT_OQ);
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = (((int*)&cmp)[i] != 0);
    }
    return result;
}

sv_mask sv_float_ge(sv_float4 a, sv_float4 b) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    __m256 cmp = _mm256_cmp_ps(a.avx_data, b.avx_data, _CMP_GE_OQ);
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = (((int*)&cmp)[i] != 0);
    }
    return result;
}

// Mask Operations
sv_mask sv_init_ones(int first_n) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = (i < first_n);
    }
    return result;
}

sv_mask sv_mask_and(sv_mask a, sv_mask b) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = a.data[i] && b.data[i];
    }
    return result;
}

sv_mask sv_mask_or(sv_mask a, sv_mask b) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = a.data[i] || b.data[i];
    }
    return result;
}

sv_mask sv_mask_not(sv_mask a) {
    sv_logger_record_unmasked_op();
    sv_mask result;
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        result.data[i] = !a.data[i];
    }
    return result;
}

bool sv_mask_all(sv_mask a) {
    sv_logger_record_unmasked_op();
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        if (!a.data[i]) {
            return false;
        }
    }
    return true;
}

bool sv_mask_any(sv_mask a) {
    sv_logger_record_unmasked_op();
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        if (a.data[i]) {
            return true;
        }
    }
    return false;
}

int sv_cntbits(sv_mask a) {
    sv_logger_record_unmasked_op();
    int count = 0;
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        if (a.data[i]) {
            count++;
        }
    }
    return count;
}

// Masked Arithmetic Operations - Integer
sv_int4 sv_int_masked_add(sv_int4 a, sv_int4 b, sv_mask mask) {
    sv_logger_record_op(mask);
    sv_int4 result = a; // Start with original values
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        if (mask.data[i]) {
            result.data[i] = a.data[i] + b.data[i];
        }
    }
    return result;
}

sv_int4 sv_int_masked_sub(sv_int4 a, sv_int4 b, sv_mask mask) {
    sv_logger_record_op(mask);
    sv_int4 result = a; // Start with original values
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        if (mask.data[i]) {
            result.data[i] = a.data[i] - b.data[i];
        }
    }
    return result;
}

sv_int4 sv_int_masked_mul(sv_int4 a, sv_int4 b, sv_mask mask) {
    sv_logger_record_op(mask);
    sv_int4 result = a; // Start with original values
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        if (mask.data[i]) {
            result.data[i] = a.data[i] * b.data[i];
        }
    }
    return result;
}

sv_int4 sv_int_masked_div(sv_int4 a, sv_int4 b, sv_mask mask) {
    sv_logger_record_op(mask);
    sv_int4 result = a; // Start with original values
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        if (mask.data[i]) {
            result.data[i] = a.data[i] / b.data[i];
        }
    }
    return result;
}

// Masked Arithmetic Operations - Float
sv_float4 sv_float_masked_add(sv_float4 a, sv_float4 b, sv_mask mask) {
    sv_logger_record_op(mask);
    sv_float4 result = a; // Start with original values
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        if (mask.data[i]) {
            result.data[i] = a.data[i] + b.data[i];
        }
    }
    return result;
}

sv_float4 sv_float_masked_sub(sv_float4 a, sv_float4 b, sv_mask mask) {
    sv_logger_record_op(mask);
    sv_float4 result = a; // Start with original values
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        if (mask.data[i]) {
            result.data[i] = a.data[i] - b.data[i];
        }
    }
    return result;
}

sv_float4 sv_float_masked_mul(sv_float4 a, sv_float4 b, sv_mask mask) {
    sv_logger_record_op(mask);
    sv_float4 result = a; // Start with original values
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        if (mask.data[i]) {
            result.data[i] = a.data[i] * b.data[i];
        }
    }
    return result;
}

sv_float4 sv_float_masked_div(sv_float4 a, sv_float4 b, sv_mask mask) {
    sv_logger_record_op(mask);
    sv_float4 result = a; // Start with original values
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        if (mask.data[i]) {
            result.data[i] = a.data[i] / b.data[i];
        }
    }
    return result;
}

// Utility Functions
std::ostream& operator<<(std::ostream& os, const sv_int4& v) {
    os << "[" << v.data[0];
    for (int i = 1; i < VECTOR_WIDTH; i++) {
        os << ", " << v.data[i];
    }
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const sv_float4& v) {
    os << "[" << v.data[0];
    for (int i = 1; i < VECTOR_WIDTH; i++) {
        os << ", " << v.data[i];
    }
    os << "]";
    return os;
}

std::ostream& operator<<(std::ostream& os, const sv_mask& m) {
    os << "[" << (m.data[0] ? "T" : "F");
    for (int i = 1; i < VECTOR_WIDTH; i++) {
        os << ", " << (m.data[i] ? "T" : "F");
    }
    os << "]";
    return os;
}