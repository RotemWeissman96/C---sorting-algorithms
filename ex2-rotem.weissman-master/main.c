#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//---------MACRO---------------
#define CORRECT_ARGS_NUM 2
#define LIST_SIZE (amount_of_bus_lines * (sizeof(BusLine)))
#define MIN_LINE_NUM 1
#define MAX_LINE_NUM 999
#define MIN_DISTANCE 0
#define MAX_DISTANCE 1000
#define MIN_DURATION 10
#define MAX_DURATION 100
#define TOO_MANY_ARGS_BUS 3
#define TEN_DECIMAL 10
#define MAX_INPUT_LEN 60
#define TEST 't'
#define BUBBLE 'b'
#define QUICK 'q'


// --------functions declaration -------
bool test_args(int argc, char *argv[]);
long get_bus_line_amount();
BusLine get_single_bus();
BusLine *get_bus_line_list(long amount_of_buses);
bool is_string_int(const char *str);
bool check_bus_line(int line_number, int distance, int duration);
bool is_three_string_int(const char *str);
int do_all_tests(BusLine *start_pt, long amount_of_bus_lines);



int main (int argc, char *argv[])
/**
 *  run the entire program, depend on input can do test/quick/bubble
 *  get user input and process it according to the command
 */
{
  if (!test_args(argc, argv)) // check if input is valid
  {
      return EXIT_FAILURE;
  }
  long amount_of_bus_lines = get_bus_line_amount();
  BusLine *pt_first_bus = get_bus_line_list(amount_of_bus_lines);
  BusLine *pt_end = pt_first_bus + amount_of_bus_lines;
  if (pt_first_bus == NULL)  // if failed to allocate memory
  {
    return EXIT_FAILURE;
  }
  switch (argv[1][0])  // switch between commands
  {
    case TEST:
      if (do_all_tests (pt_first_bus, amount_of_bus_lines) == EXIT_FAILURE)
      { // will return exit_failure only if failed to allocate memory
        free (pt_first_bus);
        return EXIT_FAILURE;
      }
      break;
    case BUBBLE:
      bubble_sort (pt_first_bus, pt_end);
      print_bus_lines_list (pt_first_bus, pt_end);
      break;
    case QUICK:
      quick_sort (pt_first_bus, pt_end);
      print_bus_lines_list (pt_first_bus, pt_end);
      break;
  }
  free(pt_first_bus);
  return EXIT_SUCCESS;
}

int do_all_tests(BusLine *start_pt, long amount_of_bus_lines)
/**
 * run all 4 test according to exercise description
 * @param start_pt
 * @param amount_of_bus_lines
 * @return fail only if there where an allocation failure
 */
{
  BusLine *copy_head_pt = malloc (LIST_SIZE);
  if (copy_head_pt == NULL)
  {
    return EXIT_FAILURE;
  }
  memcpy ( copy_head_pt, start_pt, LIST_SIZE);
  BusLine *copy_end_pt = copy_head_pt + amount_of_bus_lines;
  BusLine *end_pt = start_pt + amount_of_bus_lines;
  bubble_sort (copy_head_pt, copy_end_pt);
  is_sorted_by_distance (copy_head_pt, copy_end_pt);
  if (is_equal (copy_head_pt, copy_end_pt, start_pt, end_pt) == EXIT_FAILURE)
  {
    printf ("TEST 2 FAILED: added/lost a bus line after bubble\n");
  }
  else
  {
    printf ("TEST 2 PASSED: equal test passed after bubble\n");
  }
  quick_sort (copy_head_pt, copy_end_pt);
  is_sorted_by_duration (copy_head_pt, copy_end_pt);
  if (is_equal (copy_head_pt, copy_end_pt, start_pt, end_pt) == EXIT_FAILURE)
  {
    printf ("TEST 4 FAILED: added/lost a bus line after quick\n");
  }
  else
  {
    printf ("TEST 4 PASSED: equal test passed after quick\n");
  }
  free(copy_head_pt);
  return EXIT_SUCCESS;
}


bool test_args(int argc, char *argv[])
/**
 * check that there is only 1 argument and that it is valid
 * @param argc
 * @param argv
 * @return
 */
{
  if (argc != CORRECT_ARGS_NUM)
  {
    printf("USAGE: The number of args must be 1!\n");
    return false;
  }
  if (strcmp(argv[1], "bubble") != 0){
    if (strcmp(argv[1], "quick")!= 0){
      if (strcmp(argv[1], "test")!= 0){
        printf ("USAGE: The argument must be bubble/quick/test\n");
        return false;
      }
    }
  }
  return true;
}

long get_bus_line_amount()
/**
 * receive the number of bus lines to be expected from user
 * @return the amount of lines
 */
{
  long n = -1;
  char user_input[MAX_INPUT_LEN];
  char *str_for_test = NULL;
  printf("Enter number of lines. Then enter\n");
  fgets(user_input, MAX_INPUT_LEN, stdin);
  while ((!is_string_int (user_input)) || (n == 0) )
  {
    printf("ERROR: number of lines must be an integer bigger then 0\n");
    printf("Enter number of lines. Then enter\n");
    fgets(user_input, MAX_INPUT_LEN, stdin);
    n = strtol (user_input, &str_for_test, TEN_DECIMAL);
  }
  n = strtol (user_input, &str_for_test, TEN_DECIMAL);
  return n;
}

bool is_string_int(const char *str)
/**
 * check if a string is an integer
 * @param str
 * @return true/false
 */
{
  int i = 0;
  while ((str[i]!= '\0') && (str[i]!= '\n'))
  {
    if (isdigit(str[i]) == 0)
    {
      return false;
    }
    i++;
  }
  return true;
}

BusLine get_single_bus()
/**
 * receive a single bus information from user
 * @return the Busline object itself
 */
{
  bool is_bus_valid = false;
  int check = 0;
  char user_input[MAX_INPUT_LEN];
  int line_number = -1, distance = -1, duration = -1;
  while ( (check != TOO_MANY_ARGS_BUS) || (!is_bus_valid))
  {
    printf("Enter line info. Then enter\n");
    fgets(user_input, MAX_INPUT_LEN, stdin);
    if (!is_three_string_int (user_input))
    {
      printf("ERROR: the correct format is <number,distance,duration>");
      printf (" - make sure all positive integers\n");
      continue;
    }
    check = sscanf (user_input,"%d,%d,%d", &line_number, &distance,
                    &duration);
    is_bus_valid = check_bus_line(line_number, distance, duration);
    if (!is_bus_valid)
    {
      continue;
    }
  }
  BusLine new_bus;
  new_bus.line_number = line_number;
  new_bus.duration = duration;
  new_bus.distance = distance;
  return new_bus;
}

bool is_three_string_int(const char *str)
/**
 * checks if the user input is a valid 3 integers input
 * @param str
 * @return return true if valid and false else
 */
{
  int i = 0;
  int count_psik = 0;
  while ((str[i] != '\0') && (str[i] != '\n'))
  {
    if (str[i] == ',')
    {
      count_psik++;
      if (count_psik == TOO_MANY_ARGS_BUS)
      {
        return false;
      }
      i++;
      continue;
    }
    if (isdigit(str[i]) == 0)
    {
      return false;
    }
    i++;
  }
  return true;
}

bool check_bus_line(int line_number, int distance, int duration)
/**
 * check if all the user input is within the exercise limits
 * @param line_number
 * @param distance
 * @param duration
 * @return true/false
 */
{
  if ((line_number < MIN_LINE_NUM) || (line_number > MAX_LINE_NUM))
  {
    printf ("ERROR: the line number must be 1-999 only.\n");
    return false;
  }
  if ((distance < MIN_DISTANCE) || (distance > MAX_DISTANCE))
  {
    printf ("ERROR: the distance must be 0-1000 only.\n");
    return false;
  }
  if ((duration < MIN_DURATION) || (duration > MAX_DURATION))
  {
    printf ("ERROR: the duration must be 10 - 100 only.\n");
    return false;
  }
  return true;
}

BusLine *get_bus_line_list(long amount_of_buses)
/**
 * receive from user all the expected bus lines
 * @param amount_of_buses
 * @return a pointer to the first bus in the list / null if failed to allocate
 */
{
  BusLine *list_head_pt = malloc (amount_of_buses * sizeof(BusLine));
  if (list_head_pt == NULL)
  {
    return NULL;
  }
  for (long i = 0; i < amount_of_buses; i++)
  {
    list_head_pt[i] = get_single_bus();
  }
  return list_head_pt;
}