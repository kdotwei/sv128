#include "sv_logger.h"
#include <iostream>

// Static global variables to store the counters
static long long total_instructions = 0;
static long long utilized_lanes = 0;

// Resets all performance counters
void sv_logger_init() {
    total_instructions = 0;
    utilized_lanes = 0;
}

// Records a masked operation, counts utilized lanes
void sv_logger_record_op(sv_mask mask) {
    total_instructions++;
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        if (mask.data[i]) {
            utilized_lanes++;
        }
    }
}

// Records an operation where all lanes are utilized
void sv_logger_record_unmasked_op() {
    total_instructions++;
    utilized_lanes += VECTOR_WIDTH;
}

// Prints a summary of the collected statistics
void sv_logger_print_stats() {
    long long total_lanes = total_instructions * VECTOR_WIDTH;
    double utilization_rate = (total_lanes > 0) ? ((double)utilized_lanes / total_lanes * 100.0) : 0.0;
    
    std::cout << "\n========== Performance Statistics ==========" << std::endl;
    std::cout << "Total instructions:     " << total_instructions << std::endl;
    std::cout << "Total lanes:           " << total_lanes << std::endl;
    std::cout << "Utilized lanes:        " << utilized_lanes << std::endl;
    std::cout << "Lane utilization rate: " << utilization_rate << "%" << std::endl;
    std::cout << "============================================" << std::endl;
}