// Header file for exit.c

#ifndef EXIT_H
#define EXIT_H

#define MAX_NUM_LETTERS 12
#define MIN_MIN_LENGTH 3
#define MAX_MIN_LENGTH 5

// Exit used in case where command line is invalid in formatting.
void exit_invalid_command_line();

// Exit used in case where min length given as a command line argument is
// invalid.
void exit_invalid_min_length();

// Exit used in case where letter set given as a command line argument contains
// non-alphabetical characters.
void exit_invalid_letter_set();

// Exit used in case where letter set given as a command line argument has too
// many letters.
void exit_too_many_letters();

// Exit used in case where letter set given as as command line argument does
// not have enough letters based on the specified minimum length.
void exit_not_enough_letters(int minLength);

// Exit used in case where given dictionary file path cannot be properly opened.
void exit_invalid_dictionary_filepath(char* invalidFilePath);

// Exit used in case where a single 'q' is entered to stdin, signalling end
// of game.
void exit_end_of_game(int finalScore);

#endif /* EXIT_H */
