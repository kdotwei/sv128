#include <gtest/gtest.h>
#include "sv128.h"

// Test Case 1: Basic Integer Vector Arithmetic
TEST(SV128_Int_Arithmetic, Addition) {
    // Create input vectors using sv_set_int
    sv_int4 a = sv_set_int(1, 2, 3, 4);
    sv_int4 b = sv_set_int(10, 20, 30, 40);
    
    // Create mask to enable all computation lanes
    sv_mask mask = sv_mask_all_true();
    
    // Perform addition
    sv_int4 result = sv_int_add(a, b, mask);
    
    // Verify each element of the resulting vector
    EXPECT_EQ(result.data[0], 11);  // 1 + 10 = 11
    EXPECT_EQ(result.data[1], 22);  // 2 + 20 = 22
    EXPECT_EQ(result.data[2], 33);  // 3 + 30 = 33
    EXPECT_EQ(result.data[3], 44);  // 4 + 40 = 44
}

// Test Case 2: Floating-Point Vector Arithmetic
TEST(SV128_Float_Arithmetic, Multiplication) {
    // Create input vectors using sv_set_float
    sv_float4 a = sv_set_float(1.5f, 2.5f, 3.5f, 4.5f);
    sv_float4 b = sv_set_float(2.0f, 3.0f, 4.0f, 5.0f);
    
    // Create mask to enable all computation lanes
    sv_mask mask = sv_mask_all_true();
    
    // Perform multiplication
    sv_float4 result = sv_float_mul(a, b, mask);
    
    // Verify each element using EXPECT_FLOAT_EQ for floating-point precision
    EXPECT_FLOAT_EQ(result.data[0], 3.0f);   // 1.5 * 2.0 = 3.0
    EXPECT_FLOAT_EQ(result.data[1], 7.5f);   // 2.5 * 3.0 = 7.5
    EXPECT_FLOAT_EQ(result.data[2], 14.0f);  // 3.5 * 4.0 = 14.0
    EXPECT_FLOAT_EQ(result.data[3], 22.5f);  // 4.5 * 5.0 = 22.5
}

// Test Case 3: Verifying Masking Functionality
TEST(SV128_Masking, MaskedAddition) {
    // Create input vectors
    sv_int4 a = sv_set_int(1, 2, 3, 4);    // passthru vector
    sv_int4 b = sv_set_int(10, 20, 30, 40); // operand vector
    
    // Create custom mask [T, F, T, F] - only lanes 0 and 2 are active
    sv_mask mask;
    mask.data[0] = true;   // Lane 0: active
    mask.data[1] = false;  // Lane 1: inactive
    mask.data[2] = true;   // Lane 2: active
    mask.data[3] = false;  // Lane 3: inactive
    
    // Perform masked addition
    sv_int4 result = sv_int_add(a, b, mask);
    
    // Verify the result vector
    EXPECT_EQ(result.data[0], 11);  // Lane 0: active, 1 + 10 = 11
    EXPECT_EQ(result.data[1], 2);   // Lane 1: inactive, retains passthru value 2
    EXPECT_EQ(result.data[2], 33);  // Lane 2: active, 3 + 30 = 33
    EXPECT_EQ(result.data[3], 4);   // Lane 3: inactive, retains passthru value 4
}

// Additional test for mask operations
TEST(SV128_Masking, MaskOperations) {
    // Test sv_mask_all_true
    sv_mask all_true = sv_mask_all_true();
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        EXPECT_TRUE(all_true.data[i]);
    }
    
    // Test sv_init_ones
    sv_mask first_two = sv_init_ones(2);
    EXPECT_TRUE(first_two.data[0]);
    EXPECT_TRUE(first_two.data[1]);
    EXPECT_FALSE(first_two.data[2]);
    EXPECT_FALSE(first_two.data[3]);
    
    // Test sv_cntbits
    EXPECT_EQ(sv_cntbits(all_true), 4);
    EXPECT_EQ(sv_cntbits(first_two), 2);
}

// Test for comparison operations
TEST(SV128_Comparison, IntegerComparisons) {
    sv_int4 a = sv_set_int(1, 5, 3, 7);
    sv_int4 b = sv_set_int(2, 5, 2, 6);
    
    // Test equality
    sv_mask eq_result = sv_int_eq(a, b);
    EXPECT_FALSE(eq_result.data[0]); // 1 != 2
    EXPECT_TRUE(eq_result.data[1]);  // 5 == 5
    EXPECT_FALSE(eq_result.data[2]); // 3 != 2
    EXPECT_FALSE(eq_result.data[3]); // 7 != 6
    
    // Test less than
    sv_mask lt_result = sv_int_lt(a, b);
    EXPECT_TRUE(lt_result.data[0]);   // 1 < 2
    EXPECT_FALSE(lt_result.data[1]);  // 5 not < 5
    EXPECT_FALSE(lt_result.data[2]);  // 3 not < 2
    EXPECT_FALSE(lt_result.data[3]);  // 7 not < 6
}