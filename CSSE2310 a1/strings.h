// strings.h

#ifndef STRINGS_H
#define STRINGS_H

#include <stdio.h>
#include <stdbool.h>

#define BUFFER_SIZE 50

// Reads a line from a given file and returns it as a string (char*)
char* read_line(FILE* stream);

// Checks whether a given word is an anagrammatic subset of a given set of
// letters.
// i.e. can the word be made using the letters in the given letter set.
// Returns true if the word can be made from the letters in the letter set,
// otherwise returns false.
bool is_word_anagrammatic_subset(char* letterSet, char* word);

// Returns the number of occurences of a given letter in a given word.
// E.g. num_letter_occurences('i', "abilities") would return 3.
int num_letter_occurences(char letter, char* word);

#endif /* STRINGS_H */
