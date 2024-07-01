// Header file for arrays.c

#ifndef ARRAYS_H
#define ARRAYS_H

#include <stdbool.h>

// Checks if a given word is in a given array, provided the number of indexes
// in the array is known.
bool word_in_array(char* word, char** array, int arrayLength);

// Adds a word to an array. Accurately handles dynamic array manipulation;
// the function resizes the array to hold one more char*, then allocates
// memory for the new word at that array index.
void add_word_to_array(int* currentNumIndexes, char*** array, char* wordToAdd);

// Sorts an array in order of descending number of letters, then for each set
// of letters with the same number of letters, sorts those alphabetically.
void sort_array_desc_alpha(char*** arrayToSort, const int* arrayIndexes);

// Comparator function for qsort used in sort_array_desc_alpha. Returns positive
// int (>0) if, when comparing two words, the second should come first. Returns
// negative (<0) if the first should come before the second.
int comparator(const void* firstWord, const void* secondWord);

#endif /* ARRAYS_H */
