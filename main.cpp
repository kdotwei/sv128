#include <iostream>
#include "sv128.h"
#include "sv_logger.h"

int main() {
    // Initialize the logger
    sv_logger_init();    // Masked float multiply: " << masked_float_mul << std::endl;
    
    // Demonstrate the new getter functions
    std::cout << "\n--- Manual Performance Counter Check ---" << std::endl;
    long long total_instr = sv_logger_get_total_instructions();
    long long utilized_lanes = sv_logger_get_utilized_lanes();
    std::cout << "Retrieved via getters - Total Instructions: " << total_instr << std::endl;
    std::cout << "Retrieved via getters - Utilized Lanes: " << utilized_lanes << std::endl;
    
    // Print performance statistics
    sv_logger_print_stats(); 
    std::cout << "SV128 Library Demo - Simulated Vector 128-bit Operations" << std::endl;
    std::cout << "=========================================================" << std::endl;
    
    // Create an all-true mask for operations that need to operate on all lanes
    sv_mask all_true = sv_mask_all_true();
    
    // Integer vector operations
    std::cout << "\n--- Integer Vector Operations ---" << std::endl;
    
    // Create some integer vectors
    sv_int4 int_a = sv_set_int(1, 2, 3, 4);
    sv_int4 int_b = sv_set_int(5, 6, 7, 8);
    sv_int4 dummy_int;
    sv_int4 int_ones = sv_set1_int(dummy_int, 10, all_true);
    
    std::cout << "int_a = " << int_a << std::endl;
    std::cout << "int_b = " << int_b << std::endl;
    std::cout << "int_ones = " << int_ones << std::endl;
    
    // Basic arithmetic
    sv_int4 int_sum = sv_int_add(int_a, int_b, all_true);
    sv_int4 int_diff = sv_int_sub(int_b, int_a, all_true);
    sv_int4 int_prod = sv_int_mul(int_a, int_b, all_true);
    
    std::cout << "int_a + int_b = " << int_sum << std::endl;
    std::cout << "int_b - int_a = " << int_diff << std::endl;
    std::cout << "int_a * int_b = " << int_prod << std::endl;
    
    // Comparison operations
    sv_mask int_eq_mask = sv_int_eq(int_a, int_b, all_true);
    sv_mask int_lt_mask = sv_int_lt(int_a, int_b, all_true);
    
    std::cout << "int_a == int_b: " << int_eq_mask << std::endl;
    std::cout << "int_a < int_b:  " << int_lt_mask << std::endl;
    
    // Masked operations
    sv_int4 masked_add = sv_int_add(int_a, int_ones, int_lt_mask);
    std::cout << "masked add (where int_a < int_b): " << masked_add << std::endl;
    
    // Float vector operations
    std::cout << "\n--- Float Vector Operations ---" << std::endl;
    
    // Create some float vectors
    sv_float4 float_a = sv_set_float(1.5f, 2.5f, 3.5f, 4.5f);
    sv_float4 float_b = sv_set_float(0.5f, 1.0f, 2.0f, 3.0f);
    
    std::cout << "float_a = " << float_a << std::endl;
    std::cout << "float_b = " << float_b << std::endl;
    
    // Basic arithmetic
    sv_float4 float_sum = sv_float_add(float_a, float_b, all_true);
    sv_float4 float_prod = sv_float_mul(float_a, float_b, all_true);
    sv_float4 float_sqrt_a = sv_float_sqrt(float_a, all_true);
    
    std::cout << "float_a + float_b = " << float_sum << std::endl;
    std::cout << "float_a * float_b = " << float_prod << std::endl;
    std::cout << "sqrt(float_a) = " << float_sqrt_a << std::endl;
    
    // Advanced operations
    sv_float4 float_min = sv_float_min(float_a, float_b, all_true);
    sv_float4 float_max = sv_float_max(float_a, float_b, all_true);
    
    std::cout << "min(float_a, float_b) = " << float_min << std::endl;
    std::cout << "max(float_a, float_b) = " << float_max << std::endl;
    
    // Memory operations
    std::cout << "\n--- Memory Operations ---" << std::endl;
    
    int int_array[4] = {10, 20, 30, 40};
    float float_array[4] = {1.1f, 2.2f, 3.3f, 4.4f};
    
    sv_int4 dummy_int_load;
    sv_float4 dummy_float_load;
    sv_int4 loaded_int = sv_load_int(dummy_int_load, int_array, all_true);
    sv_float4 loaded_float = sv_load_float(dummy_float_load, float_array, all_true);
    
    std::cout << "Loaded int array: " << loaded_int << std::endl;
    std::cout << "Loaded float array: " << loaded_float << std::endl;
    
    // Store back to arrays
    int result_int[4];
    float result_float[4];
    
    sv_store_int(result_int, int_sum, all_true);
    sv_store_float(result_float, float_sum, all_true);
    
    std::cout << "Stored int sum back to array: [" << result_int[0];
    for (int i = 1; i < 4; i++) {
        std::cout << ", " << result_int[i];
    }
    std::cout << "]" << std::endl;
    
    // Mask operations
    std::cout << "\n--- Mask Operations ---" << std::endl;
    
    sv_int4 dummy_set1;
    sv_mask mask1 = sv_int_gt(sv_set_int(1, 0, 1, 0), sv_set1_int(dummy_set1, 0, all_true), all_true);
    sv_mask mask2 = sv_int_lt(int_a, sv_set1_int(dummy_set1, 3, all_true), all_true);
    
    std::cout << "mask1 (custom): " << mask1 << std::endl;
    std::cout << "mask2 (int_a < 3): " << mask2 << std::endl;
    
    sv_mask mask_and = sv_mask_and(mask1, mask2);
    sv_mask mask_or = sv_mask_or(mask1, mask2);
    sv_mask mask_not = sv_mask_not(mask2);
    
    std::cout << "mask1 AND mask2: " << mask_and << std::endl;
    std::cout << "mask1 OR mask2: " << mask_or << std::endl;
    std::cout << "NOT mask2: " << mask_not << std::endl;
    
    bool all_mask1_true = sv_mask_all(mask1);
    bool any_true = sv_mask_any(mask2);
    
    std::cout << "All true in mask1: " << (all_mask1_true ? "Yes" : "No") << std::endl;
    std::cout << "Any true in mask2: " << (any_true ? "Yes" : "No") << std::endl;
    
    // More masked operations
    sv_float4 masked_float_mul = sv_float_mul(float_a, float_b, mask2);
    std::cout << "Masked float multiply: " << masked_float_mul << std::endl;
    
    // Print performance statistics
    sv_logger_print_stats();
    
    return 0;
}