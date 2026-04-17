#include "sv_logger.h"
#include <iostream>

// Static global variables to store the counters
static long long total_instructions = 0;
static long long utilized_lanes = 0;
static long long total_clock_cost = 0;

// Resets all performance counters
void sv_logger_init() {
    total_instructions = 0;
    utilized_lanes = 0;
    total_clock_cost = 0;
}

// Records a masked vector operation
void sv_logger_record_op(sv_mask mask, int clock_cost) {
    total_instructions++;
    total_clock_cost += clock_cost;
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        if (mask.data[i]) {
            utilized_lanes++;
        }
    }
}

// Records a full-width vector operation (all lanes active)
void sv_logger_record_unmasked_op(int clock_cost) {
    total_instructions++;
    utilized_lanes += VECTOR_WIDTH;
    total_clock_cost += clock_cost;
}

// Records a scalar (SimFloat) operation — 1 lane utilized
void sv_logger_record_scalar_op(int clock_cost) {
    total_instructions++;
    utilized_lanes += 1;
    total_clock_cost += clock_cost;
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
    std::cout << "Total clock cost:      " << total_clock_cost << " cycles" << std::endl;
    std::cout << "============================================" << std::endl;
}

// Implementation for getter functions
long long sv_logger_get_total_instructions() {
    return total_instructions;
}

long long sv_logger_get_utilized_lanes() {
    return utilized_lanes;
}

long long sv_logger_get_total_clock_cost() {
    return total_clock_cost;
}