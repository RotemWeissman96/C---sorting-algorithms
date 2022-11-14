#include <stdlib.h>
#include "test_bus_lines.h"
#include <stdio.h>
#include <stdbool.h>
// add implementation here


// ---------function declaration----------



// ----------function implementation--------------

int is_sorted_by_distance (BusLine *start, BusLine *end)
/**
 * checks if the list is sorted by the distance
 * @param start
 * @param end
 */
{
  int temp = 0;
  while (start != end)
  {
    if (start->distance < temp)
    {
      printf ("TEST 1 FAILED: Test by distance Failed\n");
      return EXIT_FAILURE;
    }
    temp = start->distance;
    start += 1;
  }
  printf ("TEST 1 PASSED: Test by distance Passed\n");
  return EXIT_SUCCESS;
}

int is_sorted_by_duration (BusLine *start, BusLine *end)
/**
 * checks if the list is sorted by the duration
 * @param start
 * @param end
 */
{
  int temp = 0;
  while (start != end)
  {
    if (start->duration < temp)
    {
      printf ("TEST 3 FAILED: Test by duration Failed\n");
      return EXIT_FAILURE;
    }
    temp = start->duration;
    start += 1;
  }
  printf ("TEST 3 PASSED: Test by duration Passed\n");
  return EXIT_SUCCESS;
}

int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original)
/**
* checks if two lists are equals
* @param start
* @param end
*/
{
  int current_line = 0;
  bool found = false;
  BusLine *start_original_temp = start_original;
  if ((end_sorted - start_sorted) != (end_original - start_original))
  {  // check if the list are with same length
    return false;
  }
  while(start_sorted != end_sorted)
  {
    current_line = start_sorted->line_number;
    while((start_original != end_original))
    {
      if (current_line == start_original->line_number)
      {
        if (!found)
        {
          found = true;
        }
        else // if already found
        {
          //printf ("test failed - a line was duplicated - dont submit me\n");
          return EXIT_FAILURE;
        }
      }
      start_original += 1;
    }
    if (!found)
    {
      //printf ("test failed - a line was missing - dont submit me\n");
      return EXIT_FAILURE;
    }
    start_original = start_original_temp;
    found = false;
    start_sorted += 1;
  }
  return EXIT_SUCCESS;
}
