// Modular array manipulation and handling functions.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "arrays.h"

bool word_in_array(char* word, char** array, int arrayLength)
{
    for (int i = 0; i < arrayLength; i++) {
        if (strcmp(array[i], word) == 0) {
            return true;
        }
    }
    return false;
}

void add_word_to_array(int* currentNumIndexes, char*** array, char* wordToAdd)
{
    // Resize array to accomodate another char*
    (*currentNumIndexes)++;
    *array = realloc(*array, *currentNumIndexes * sizeof(**array));
    // Check to make sure realloc worked
    if (*array == NULL) {
        free(*array);
    }
    // Malloc space for new word to occupy
    int wordIndex = *currentNumIndexes - 1;
    (*array)[wordIndex] = malloc((strlen(wordToAdd) + 1) * sizeof(char));
    // Check to make sure malloc worked
    if ((*array)[wordIndex] == NULL) {
        free((*array)[wordIndex]);
    }
    // Add word
    strcpy((*array)[wordIndex], wordToAdd);
}

void sort_array_desc_alpha(char*** arrayToSort, const int* arrayIndexes)
{
    // qsort as recommended by task sheet
    qsort((void*)*arrayToSort, *arrayIndexes, sizeof(*arrayToSort[0]),
            comparator);
}

int comparator(const void* firstWord, const void* secondWord)
{
    // Between two words, the short one should go first.
    // If they are of equal length, they should be sorted alphabetically.

    // Return greater than 0 if secondWord goes before firstWord
    // Return less than 0 if firstWord goes before secondWord
    // I hate pointers.
    // REF: The following line of code is inspired by the code at
    // REF: https://www.geeksforgeeks.org/c-program-sort-array-names-strings/
    const char* word1 = *(const char**)firstWord;
    const char* word2 = *(const char**)secondWord;
    int ret;

    if (strlen(word1) != strlen(word2)) {
        // First return based on length
        ret = strlen(word1) - strlen(word2);
    } else {
        // strcmp returns greater than 0 if firstWord comes after secondWord
        // alphabetically, strcmp returns less than 0 if secondWord comes after
        // firstWord alphabetically
        // REF: The following line of code is inspired by the code at
        // REF: https://www.geeksforgeeks.org/c-program-sort-array-names-strings
        // REF: /
        ret = strcmp(word1, word2);
    }
    return ret;
    // Return zero if firstWord is equal to secondWord
    // ^ Shouldn't be the case because parse_dictionary filters out duplicates
}
