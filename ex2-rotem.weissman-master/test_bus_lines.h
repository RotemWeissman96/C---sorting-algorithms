#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
/**
 *  add documentation
 */
int is_sorted_by_distance (BusLine *start, BusLine *end);
/**
 *  add documentation
 */
int is_sorted_by_duration (BusLine *start, BusLine *end);
/**
 *  add documentation
 */
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
#endif //EX2_REPO_TESTBUSLINES_H
