#ifndef SV_LOGGER_H
#define SV_LOGGER_H

#include "sv128.h"

// Function Declarations
void sv_logger_init(); // Resets all performance counters
void sv_logger_record_op(sv_mask mask, int clock_cost); // Records a masked vector operation
void sv_logger_record_unmasked_op(int clock_cost); // Records a full-width vector operation
void sv_logger_record_scalar_op(int clock_cost); // Records a scalar (SimFloat) operation (1 lane)
void sv_logger_print_stats(); // Prints a summary of the collected statistics

// Getter functions to access performance counters
long long sv_logger_get_total_instructions();
long long sv_logger_get_utilized_lanes();
long long sv_logger_get_total_clock_cost();

#endif // SV_LOGGER_H