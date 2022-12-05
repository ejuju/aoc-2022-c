#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://adventofcode.com/2022/day/1
// Find the elf carrying the most calories

int main(void) {
  // Open input file
  char *filepath = "input.txt";
  FILE *input_file = fopen(filepath, "r");
  if (input_file == NULL) {
    printf("failed to open input file at %s", filepath);
    exit(1);
  };

  // Find max calories
  int max_calories = 0;
  int curr_calories = 0;
  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, input_file) != -1) {
    line[strlen(line) - 1] = '\0'; // strip trailing line return from string
    if (strcmp(line, "\0") == 0) {
      if (curr_calories > max_calories) {
        max_calories = curr_calories;
      }
      curr_calories = 0;
      continue;
    }
    curr_calories += atoi(line);
  }

  // Print result
  printf("max calories: %d\n", max_calories);

  // Free resources
  free(line);
  fclose(input_file);
}
