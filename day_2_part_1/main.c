#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum option { rock = 1, paper, scissors };
enum score { loss, draw = 3, win = 6 };

enum option charToOption(char c) {
  switch (c) {
  case 'A':
    return rock;
  case 'X':
    return rock;
  case 'B':
    return paper;
  case 'Y':
    return paper;
  case 'C':
    return scissors;
  case 'Z':
    return scissors;
  }
  return -1;
}

enum score play(enum option player, enum option opponent) {
  if (player == opponent) {
    return draw;
  } else if (player == rock) {
    return opponent == scissors ? win : loss;
  } else if (player == scissors) {
    return opponent == paper ? win : loss;
  } else if (player == paper) {
    return opponent == rock ? win : loss;
  }
  return -1;
}

int main(void) {
  // Open input file
  char *filepath = "input.txt";
  FILE *input_file = fopen(filepath, "r");
  if (input_file == NULL) {
    printf("failed to open input file at %s", filepath);
    exit(1);
  };

  // Calculate total score
  int total_score = 0;
  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, input_file) != -1) {
    // strip last character (trailing line return)
    if (line[strlen(line) - 1] == '\n') {
      line[strlen(line) - 1] = '\0';
    }

    // split string to get opponent and player choices
    char *opponent_option = strtok(line, " ");
    char *player_option = strtok(NULL, " ");

    // Convert letter to option
    enum option opponent_opt = charToOption(opponent_option[0]);
    enum option player_opt = charToOption(player_option[0]);

    // Calculate outcome
    enum score outcome = play(player_opt, opponent_opt);

    // Increase score with outcome and player choice
    total_score += outcome + player_opt;
  }

  // Print result
  printf("total score: %d\n", total_score);

  // Free resources
  free(line);
  fclose(input_file);
}
