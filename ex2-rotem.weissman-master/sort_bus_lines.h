#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
#include "sort_bus_lines.h"
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
/**
 *  add documentation
 */
typedef struct BusLine
{
    int line_number, distance, duration;
} BusLine;

/**
 * add documentation
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 *  add documentation
 */
void quick_sort (BusLine *start, BusLine *end);

/**
 *  add documentation
 */
BusLine *partition (BusLine *start, BusLine *end);
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
void print_bus_lines_list(BusLine *start, BusLine *end);


#endif //EX2_REPO_SORTBUSLINES_H
