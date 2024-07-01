/*
 * exit.c
 *
 * Handles exits with appropriate error messages and exit statuses.
 */

#include <stdio.h>
#include <stdlib.h>
#include "exit.h"

// Definition of exit codes and their values.
enum ExitCodes {
    EXIT_INVALID_COMMAND_LINE = 18,
    EXIT_INVALID_MIN_LENGTH = 3,
    EXIT_INVALID_LETTER_SET = 6,
    EXIT_TOO_MANY_LETTERS = 7,
    EXIT_NOT_ENOUGH_LETTERS = 1,
    EXIT_INVALID_DICTIONARY = 16,
    EXIT_FINAL_SCORE = 0,
    EXIT_NO_FINAL_SCORE = 2
};

// Function docstrings can be found in exit.h

void exit_invalid_command_line()
{
    fprintf(stderr,
            "Usage: uqunscramble [--length-min length] [--dictionary file] "
            "[--lett letters]\n");
    exit(EXIT_INVALID_COMMAND_LINE);
}

void exit_invalid_min_length()
{
    fprintf(stderr,
            "uqunscramble: min length value must be between %i and %i\n",
            MIN_MIN_LENGTH, MAX_MIN_LENGTH);
    exit(EXIT_INVALID_MIN_LENGTH);
}

void exit_invalid_letter_set()
{
    fprintf(stderr, "uqunscramble: set of letters is invalid\n");
    exit(EXIT_INVALID_LETTER_SET);
}

void exit_too_many_letters()
{
    fprintf(stderr, "uqunscramble: too many letters - the limit is %i\n",
            MAX_NUM_LETTERS);
    exit(EXIT_TOO_MANY_LETTERS);
}

void exit_not_enough_letters(int minLength)
{
    fprintf(stderr,
            "uqunscramble: more letters required for the given minimum length "
            "(%i)\n",
            minLength);
    exit(EXIT_NOT_ENOUGH_LETTERS);
}

void exit_invalid_dictionary_filepath(char* invalidFilePath)
{
    fprintf(stderr,
            "uqunscramble: dictionary file named \"%s\" cannot be opened\n",
            invalidFilePath);
    exit(EXIT_INVALID_DICTIONARY);
}

void exit_end_of_game(int finalScore)
{
    if (finalScore > 0) {
        fprintf(stdout, "Game over. Final score is %i\n", finalScore);
        exit(EXIT_FINAL_SCORE);
    } else {
        fprintf(stdout, "No valid guesses\n");
        exit(EXIT_NO_FINAL_SCORE);
    }
}
