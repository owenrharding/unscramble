/*
 * strings.c
 *
 * Modular functions related to string input and checking.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "strings.h"

// REF: The following code is a modified version of the code from Ed Lessons:
// REF: 3.2 - Write to the filesystem
char* read_line(FILE* stream)
{
    int bufferSize = BUFFER_SIZE;
    char* buffer = malloc(sizeof(char) * bufferSize);
    int numRead = 0;
    int next;

    if (feof(stream)) {
        return NULL;
    }

    while (1) {
        next = fgetc(stream);
        // If no characters have been encountered yet and it's already the end
        // of the file, then return NULL
        if (next == EOF && numRead == 0) {
            free(buffer);
            return NULL;
        }
        // Extend buffer size if it reaches full capacity.
        if (numRead == bufferSize - 1) {
            bufferSize *= 2;
            buffer = realloc(buffer, sizeof(char) * bufferSize);
        }
        // Stops reading if it hits the end of the line/file.
        if (next == '\n' || next == EOF) {
            buffer[numRead] = '\0';
            break;
        }
        // Save characters as uppercase so it's easier for comparison and later
        // for advanced functionality.
        buffer[numRead++] = toupper(next);
    }
    return buffer;
}

bool is_word_anagrammatic_subset(char* letterSet, char* word)
{
    // Counts the number of occurences for each letter in word
    for (size_t i = 0; i < strlen(word); i++) {
        char letter = word[i];
        // If there are more occurences of the letter in the word, than in the
        // letter set, then logically the letter set letters cannot make the
        // word.
        if (num_letter_occurences(letter, letterSet)
                >= num_letter_occurences(letter, word)) {
            continue;
        }
        return false;
    }
    return true;
}

int num_letter_occurences(char letter, char* word)
{
    int letterCount = 0;
    for (size_t i = 0; i < strlen(word); i++) {
        // Use tolower to get rid of problem comparing upper and lower case
        if (tolower(letter) == tolower(word[i])) {
            letterCount++;
        }
    }
    return letterCount;
}
