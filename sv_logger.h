#ifndef SV_LOGGER_H
#define SV_LOGGER_H

#include "sv128.h"

// Function Declarations
void sv_logger_init(); // Resets all performance counters
void sv_logger_record_op(sv_mask mask); // Records a masked operation, counts utilized lanes
void sv_logger_record_unmasked_op(); // Records an operation where all lanes are utilized
void sv_logger_print_stats(); // Prints a summary of the collected statistics

#endif // SV_LOGGER_H