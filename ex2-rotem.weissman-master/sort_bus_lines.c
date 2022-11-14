#include <stddef.h>
#include <stdio.h>
#include "sort_bus_lines.h"



// -------------functions declarations -------------
void switch_lines (BusLine *line1, BusLine *line2);



//--------------functions implementation--------------

void bubble_sort (BusLine *start, BusLine *end)
/**
 * sort the list with bubble sort by distance
 * @param start
 * @param end
 */
{
  BusLine *current_line = start + 1;
  BusLine *current_end = end;
  while (current_end != start)
  {
    while (current_end != current_line)
    {
      if ((current_line-1)->distance > current_line->distance)
      {
        switch_lines (current_line, current_line-1);
      }
      current_line += 1;
    }
    current_line = start + 1;
    current_end -= 1;
  }
}

void switch_lines (BusLine *line1, BusLine *line2)
/**
 * switch the values of 2 bus lines in the line list
 * @param line1
 * @param line2
 */
{
  BusLine temp;
  temp.line_number = line1->line_number;
  temp.distance = line1->distance;
  temp.duration = line1->duration;
  line1->line_number = line2->line_number;
  line1->distance = line2->distance;
  line1->duration = line2->duration;
  line2->line_number = temp.line_number;
  line2->distance = temp.distance;
  line2->duration = temp.duration;
}

void quick_sort (BusLine *start, BusLine *end)
/**
 * sort the list with quick sort by duration
 * @param start
 * @param end
 */
{
  if(start == end)
  {
    return;
  }
  BusLine *pivot = partition (start, end);
  quick_sort (start, pivot);
  quick_sort (pivot + 1, end);
}

BusLine *partition (BusLine *start, BusLine *end)
/**
 * sort the list in a way that all of the samller the pivor will be at the
 * beginning of the list and all the bigger then pivot will be at the end.
 * the pivot will be at the right place in a sorted list
 * @param start
 * @param end
 */
{
  BusLine *pivot = end-1;
  BusLine *current_line = start;
  int i = 0;
  while (current_line != pivot)
  {
    if (current_line->duration < pivot->duration)
    {
      switch_lines (current_line, start + i);
      i += 1;
    }
    current_line += 1;
  }
  switch_lines (pivot, start+i);
  return start + i;
}

void print_bus_lines_list(BusLine *start, BusLine *end)
{
  /**
 * sprints to stdout the entire list
 * @param start
 * @param end
 */
  while (start != end)
  {
    printf ("%d,", start->line_number);
    printf ("%d,", start->distance);
    printf ("%d\n", start->duration);
    start += 1;
  }
}