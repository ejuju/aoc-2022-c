#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://adventofcode.com/2022/day/1
// Find the total calories carried by the top 3 elfs.

int main(void) {
  // Open input file
  char *filepath = "input.txt";
  FILE *input_file = fopen(filepath, "r");
  if (input_file == NULL) {
    printf("failed to open input file at %s", filepath);
    exit(1);
  };

  // Find total calories for top 3 elves
  int top_calories[3] = {0, 0, 0};
  size_t num_top = sizeof(top_calories) / sizeof(top_calories[0]);
  printf("looking for top %lu elves\n", num_top);
  int curr_calories = 0;
  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, input_file) != -1) {
    // strip trailing line return from string
    line[strlen(line) - 1] = '\0';
    // when line is not a line break, just increment calory counter and continue
    if (strcmp(line, "\0") != 0) {
      curr_calories += atoi(line);
      continue;
    }

    // Check if curr calories is larger than any of the top 3 values
    for (int i = 0; i < num_top; i++) {
      if (curr_calories > top_calories[i]) {
        // shift next values
        for (int j = i; j < num_top - 1; j++) {
          top_calories[j + 1] = top_calories[j];
        }
        top_calories[i] = curr_calories;
        break;
      }
    }
    curr_calories = 0;
  }

  // Print result
  int total_calories = 0;
  for (int i = 0; i < num_top; ++i) {
    printf("top elf %d is carrying %d calories\n", i, top_calories[i]);
    total_calories += top_calories[i];
  }
  printf("total calories: %d\n", total_calories);

  // Free resources
  free(line);
  fclose(input_file);
}
