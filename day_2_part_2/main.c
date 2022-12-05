#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum option { rock = 1, paper, scissors };
enum outcome { loss, draw = 3, win = 6 };

enum option char_to_option(char c) {
  switch (c) {
  case 'A':
    return rock;
  case 'B':
    return paper;
  case 'C':
    return scissors;
  }
  return -1;
}

enum outcome char_to_outcome(char c) {
  switch (c) {
  case 'X':
    return loss;
  case 'Y':
    return draw;
  case 'Z':
    return win;
  }
  return -1;
}

enum option option_for_outcome(enum option opponent, enum outcome want) {
  if (want == draw) {
    return opponent;
  } else if (opponent == rock) {
    return want == win ? paper : scissors;
  } else if (opponent == scissors) {
    return want == win ? rock : paper;
  } else if (opponent == paper) {
    return want == win ? scissors : rock;
  }
  return -1;
}

enum outcome play(enum option player, enum option opponent) {
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

    // split string to get opponent and desired outcome
    char *opponent_choice = strtok(line, " ");
    char *desired_outcome_str = strtok(NULL, " ");

    // Calculate option to choose to reach desired outcome
    enum option opponent_opt = char_to_option(opponent_choice[0]);
    enum outcome desired_outcome = char_to_outcome(desired_outcome_str[0]);
    enum option player_opt = option_for_outcome(opponent_opt, desired_outcome);

    // Increase score with outcome and player choice
    total_score += desired_outcome + player_opt;
  }

  // Print result
  printf("total score: %d\n", total_score);

  // Free resources
  free(line);
  fclose(input_file);
}
