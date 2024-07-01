// s4800761 uqunscramble a1

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <csse2310a1.h>

// Included files
#include "strings.h"
#include "arrays.h"
#include "exit.h"

// Constants
#define DEFAULT_DICT_PATH "/local/courses/csse2310/etc/words"
#define DEFAULT_NUM_LETTERS 9
#define DEFAULT_MIN_LENGTH 4
#define MAX_NUM_CMD_ARGS 7
#define MIN_MIN_LENGTH 3
#define MAX_MIN_LENGTH 5
#define MAX_NUM_LETTERS 12
#define ALL_LETTERS_BONUS 10

#define ARG_IS_OPTION_LETT 50
#define ARG_IS_OPTION_DICT 51
#define ARG_IS_OPTION_LENGTH 52
#define ARG_IS_NOT_OPTION_SPECIFIER 53

// Struct that models a single game and its attributes
typedef struct {
    char* letters;
    char* dictionaryName;
    int minLength;
    int lettersLength;
    FILE* dictionary;
    char** validWordsArray;
    int wordIndexes;
    char** validGuessesArray;
    int guessIndexes;
    int score;

    bool lettersPresent;
    bool dictionaryNamePresent;
    bool minLengthPresent;
} Game;

// Function declarations
void check_command_args(int argc, char** argv, Game* game);
int check_string_is_option_arg(char* argument);
void set_command_args(int argc, char** argv, Game* game);
void check_letter_set(Game* game);
void check_min_length(Game* game);
void check_and_set_dictionary(Game* game);
void parse_dictionary(Game* game);
void run_game(Game* game);
bool word_is_valid_length(Game* game, char* word);
bool process_guess(Game* game);
void clean_array(char*** array, int arrayIndexes);
void clean_game(Game* game);
bool arg_present_already(char* currentArg, Game* game);
void init_game(Game* game);
bool valid_guess(Game* game, char* guess);

int main(int argc, char** argv)
{
    Game* game = malloc(sizeof(Game));
    init_game(game);

    // Command Line Argument Checking
    check_command_args(argc, argv, game);
    set_command_args(argc, argv, game);

    // Length Validity Checking
    check_min_length(game);

    // Letter Set Checking
    check_letter_set(game);

    // Dictionary File Name Checking
    check_and_set_dictionary(game);

    // Extract valid words from dictionary
    parse_dictionary(game);

    // Prompts and evaluates user input
    run_game(game);
}

// Initialises preliminary game attributes.
void init_game(Game* game)
{
    if (game != NULL) {
        // Initialise to 4 by default, overwrite if --length-min is passed to
        // command line.
        game->minLength = DEFAULT_MIN_LENGTH;
        game->lettersPresent = false;
        game->dictionaryNamePresent = false;
        game->minLengthPresent = false;
        game->wordIndexes = 0;
        game->guessIndexes = 0;
        game->letters = NULL;
        game->dictionaryName = NULL;
        game->lettersLength = 0;
        game->dictionary = NULL;
        game->validWordsArray = NULL;
        game->validGuessesArray = NULL;
        game->score = 0;
    }
}

// Prints welcome message and continuously prompts user for input
void run_game(Game* game)
{
    fprintf(stdout, "Welcome to UQunscramble!\n");
    fprintf(stdout,
            "Enter words of length %i to %i made from the letters \"%s\"\n",
            game->minLength, game->lettersLength, game->letters);

    // Continuously prompt for a guess, and respond accordingly.
    // Exit is handled in process_guess.
    while (1) {
        process_guess(game);
    }
}

// Responds to 'q' being entered as a guess. Prints out all possible words that
// can be made from the letter set, the maximum possible score, and the user's
// score.
void quit_game(Game* game)
{
    int maxPossibleScore = 0;
    // Loop through valid words, printing and calculating score as it goes.
    for (int i = 0; i < game->wordIndexes; i++) {
        fprintf(stdout, "%s\n", game->validWordsArray[i]);
        maxPossibleScore += strlen(game->validWordsArray[i]);
        if (strlen(game->validWordsArray[i]) == (size_t)game->lettersLength) {
            maxPossibleScore += ALL_LETTERS_BONUS;
        }
    }
    fprintf(stdout, "The maximum possible score is %i\n", maxPossibleScore);

    // Save score in temp variable so struct can be free-d.
    int score = game->score;
    clean_game(game);
    exit_end_of_game(score);
}

// Frees variables malloc-ed throughout the game.
void clean_game(Game* game)
{
    clean_array(&game->validWordsArray, game->wordIndexes);
    clean_array(&game->validGuessesArray, game->guessIndexes);
    free(game->letters);
    free(game->dictionaryName);
    free(game);
}

// Reads user input (guess), and if it is a valid guess, adds it to
// validGuessArray in Game struct.
// Updates score in Game struct.
// Prints score to user given a valid guess.
bool process_guess(Game* game)
{
    char* inputLine = read_line(stdin);
    // Check if inputLine is NULL (end of file or error)
    if (inputLine == NULL) {
        exit_end_of_game(game->score);
    }
    if (inputLine[0] == 'Q') {
        quit_game(game);
    }

    if (valid_guess(game, inputLine) == false) {
        free(inputLine);
        return false;
    }

    // Word is valid if passed the above tests
    add_word_to_array(&game->guessIndexes, &game->validGuessesArray, inputLine);

    // Update and print score
    game->score += strlen(inputLine);
    if (strlen(inputLine) == (size_t)game->lettersLength) {
        game->score += ALL_LETTERS_BONUS;
    }
    fprintf(stdout, "OK! Your score so far is %i\n", game->score);
    free(inputLine);
    return true;
}

// Logic behind checking whether a guess is valid.
// Prints situational error messages if an invalid guess is given.
// Returns false if it is an invalid guess, otherwise returns true.
bool valid_guess(Game* game, char* guess)
{
    // Loop through characters to see if any are non-alphabetical
    for (size_t i = 0; i < strlen(guess); i++) {
        // isaplha == 0 -> character is non-alphabetical
        if (isalpha(guess[i]) == 0) {
            fprintf(stdout,
                    "Guess must contain only uppercase and/or lowercase "
                    "letters\n");
            return false;
        }
    }
    // Check that word entered is neither too long nor short
    if (word_is_valid_length(game, guess) == false) {
        if (strlen(guess) < (size_t)game->minLength) {
            fprintf(stdout,
                    "Word too short - it must have at least %i characters\n",
                    game->minLength);
        } else {
            fprintf(stdout, "Word must be no more than %i characters long\n",
                    game->lettersLength);
        }
        return false;
    }
    // Check if the entered word can be made from the letter set
    if (is_word_anagrammatic_subset(game->letters, guess) == false) {
        fprintf(stdout, "Word can't be formed with available letters\n");
        return false;
    }
    // Check if the entered word has already been entered
    if (word_in_array(guess, game->validGuessesArray, game->guessIndexes)
            == true) {
        fprintf(stdout, "Word has been guessed earlier\n");
        return false;
    }
    // Check if entered word is a valid word in dictionary
    if (word_in_array(guess, game->validWordsArray, game->wordIndexes)
            == false) {
        fprintf(stdout, "Word can't be found in the dictionary\n");
        return false;
    }
    return true;
}

// Checks if the dictionary file name stored in struct can be opened without
// issues. Exits if not, but if it can, it opens it and stores the FILE* in
// Game struct.
void check_and_set_dictionary(Game* game)
{
    // Check given dictionary filepath is valid and leads to an openable FILE*
    FILE* openDictionary = fopen(game->dictionaryName, "r");
    if (openDictionary == NULL) {
        exit_invalid_dictionary_filepath(game->dictionaryName);
    } else {
        game->dictionary = openDictionary;
    }
}

// Checks if a word is within the length bounds defined in Game struct.
bool word_is_valid_length(Game* game, char* word)
{
    int wordLength = strlen(word);
    if (wordLength >= game->minLength && wordLength <= game->lettersLength) {
        return true;
    }
    return false;
}

// Reads dictionary file line by line and adds the word on a line IF it is a
// valid word.
// Done this way because saves having to do the intermediate step of saving
// every word to an array, then going through the array, then saving valid
// words from there.
void parse_dictionary(Game* game)
{
    game->validWordsArray = malloc(sizeof(char*));

    // Continuously read the next line until end of file is detected.
    while (!feof(game->dictionary)) {
        char* buffer = read_line(game->dictionary);
        if (buffer == NULL) {
            free(buffer);
            continue;
        }
        // If word is too short/too long, then not a valid word so don't add
        // Do this before letter set check because strlen takes less time than
        // checking occurance of every letter.
        if (word_is_valid_length(game, buffer) == false) {
            free(buffer);
            continue;
        }
        // If word can't be made from letter set, don't add
        if (is_word_anagrammatic_subset(game->letters, buffer) == false) {
            free(buffer);
            continue;
        }
        // Don't add duplicates
        if (game->validWordsArray != NULL
                && word_in_array(
                           buffer, game->validWordsArray, game->wordIndexes)
                        == true) {
            free(buffer);
            continue;
        }

        // If it's gotten to this point, word is valid. Add to valid words array
        add_word_to_array(&game->wordIndexes, &game->validWordsArray, buffer);

        free(buffer);
    }

    // Close to prevent memory leaks
    fclose(game->dictionary);
    // Sort now, that way don't have to do it later for advanced func
    sort_array_desc_alpha(&game->validWordsArray, &game->wordIndexes);
}

// Frees malloc-ed memory of dynamically allocated array.
// Char*** because pointer to char**
void clean_array(char*** array, int arrayIndexes)
{
    // First free all strings
    for (int i = 0; i < arrayIndexes; i++) {
        // *array[i] doesn't work because of operator precedence (I think)
        // Wasn't working so just randomly tried different things and (*array)
        // worked so I kept it.
        free((*array)[i]);
    }
    // Then free array holding the strings
    free(*array);
}

// Checks to see if the command line is formatted correctly.
// Exits appropriately if not.
void check_command_args(int argc, char** argv, Game* game)
{
    // Check that args are in pairs (following the executable name)
    // and that there are at most 6
    if (((argc - 1) % 2 != 0) || argc > MAX_NUM_CMD_ARGS) {
        exit_invalid_command_line();
    }

    // Start at i = 1 to ignore argv[0] which is the executable
    for (int i = 1; i < argc; i += 2) {
        char* currentArg = argv[i];
        char* nextArg = argv[i + 1];
        // For loop starts at the second command argument, which should be an
        // option specifier, and increments in two, which means every current
        // arg should be an option specifier.
        if (check_string_is_option_arg(currentArg)
                == ARG_IS_NOT_OPTION_SPECIFIER) {
            exit_invalid_command_line();
        }
        // If this string is option specifier and next string is option
        // specifier then no parameter was given
        if (check_string_is_option_arg(nextArg)
                != ARG_IS_NOT_OPTION_SPECIFIER) {
            exit_invalid_command_line();
        }
        // Translation: if this argument is --length-min and next argument is
        // not a single digit, then fail
        if (check_string_is_option_arg(currentArg) == ARG_IS_OPTION_LENGTH) {
            if (strlen(nextArg) != 1) {
                exit_invalid_command_line();
            }
            if (isdigit(nextArg[0]) == 0) {
                exit_invalid_command_line();
            }
        }
        if (arg_present_already(currentArg, game) == true) {
            exit_invalid_command_line();
        }
        // If arg is not a valid option specifier yet still contains -- then
        // fail
        if ((check_string_is_option_arg(currentArg)
                    == ARG_IS_NOT_OPTION_SPECIFIER)
                && (strstr(currentArg, "--") != NULL)) {
            exit_invalid_command_line();
        }
    }
}

// Sees if an option specifier in the command line has already occurred
// (checking for duplicates of --lett, --dictionary, or --length-min).
// If it hasn't encountered the one that it's checking, it sets it to
// 'encountered' for the next time around.
bool arg_present_already(char* currentArg, Game* game)
{
    // Identify which option specifier argument was passed into this function.
    switch (check_string_is_option_arg(currentArg)) {
    case ARG_IS_OPTION_LETT:
        // If --lett has already occured, it will have already been set as true:
        // therefore, return true that arg is present already.
        if (game->lettersPresent == true) {
            return true;
        }
        // If lettersPresent is not true, then --lett must not have occurred
        // yet. So, set lettersPresent as true for next time.
        else {
            game->lettersPresent = true;
        }
        break;
    case ARG_IS_OPTION_DICT:
        if (game->dictionaryNamePresent == true) {
            return true;
        } else {
            game->dictionaryNamePresent = true;
        }
        break;
    case ARG_IS_OPTION_LENGTH:
        if (game->minLengthPresent == true) {
            return true;
        } else {
            game->minLengthPresent = true;
        }
        break;
    }
    return false;
}

// Use this function after the command line has been CHECKED.
// Sets struct command line values as corresponding values from command line
// (that sounds really confusing but not sure how else to say it).
// If an option specifier (--blah) is given, then sets corresponding.
// If not, sets default.
void set_command_args(int argc, char** argv, Game* game)
{
    for (int i = 1; i < argc; i += 2) {
        char* currentArg = argv[i];
        char* nextArg = argv[i + 1];

        // Go through argv, check if arg is option specifier, then set following
        // arg to corresponding variable of that type
        switch (check_string_is_option_arg(currentArg)) {
        case ARG_IS_OPTION_LETT:
            game->letters = malloc((strlen(nextArg) + 1) * sizeof(char));
            strcpy(game->letters, nextArg);
            break;
        case ARG_IS_OPTION_DICT:
            game->dictionaryName = malloc((strlen(nextArg) + 1) * sizeof(char));
            strcpy(game->dictionaryName, nextArg);
            break;
        case ARG_IS_OPTION_LENGTH:
            game->minLength = atoi(nextArg);
            break;
        }
    }

    // If letter set wasn't specified, then set default
    if (game->lettersPresent == false) {
        // Random letters function from csse2310a1.h
        const char* randomLetters = get_random_letters(DEFAULT_NUM_LETTERS);
        game->letters = malloc((DEFAULT_NUM_LETTERS + 1) * sizeof(char));
        strcpy(game->letters, randomLetters);
    }
    // If dictionary name wasn't specified, then set default
    if (game->dictionaryNamePresent == false) {
        game->dictionaryName
                = malloc((strlen(DEFAULT_DICT_PATH) + 1) * sizeof(char));
        strcpy(game->dictionaryName, DEFAULT_DICT_PATH);
    }
    // Doesn't set default min length because min length was default intialised
    // to 4 in init_game (because it doesn't need dynamic memory).

    game->lettersLength = strlen(game->letters);
}

// Checks if a string, presumably from a command line argument, is an option
// specifier.
int check_string_is_option_arg(char* argument)
{
    if (strcmp(argument, "--lett") == 0) {
        return ARG_IS_OPTION_LETT;
    }
    if (strcmp(argument, "--dictionary") == 0) {
        return ARG_IS_OPTION_DICT;
    }
    if (strcmp(argument, "--length-min") == 0) {
        return ARG_IS_OPTION_LENGTH;
    }
    return ARG_IS_NOT_OPTION_SPECIFIER;
}

// Checks if the min length is within the given bounds and exits appropriately
// if not.
void check_min_length(Game* game)
{
    if (game->minLength < MIN_MIN_LENGTH || game->minLength > MAX_MIN_LENGTH) {
        exit_invalid_min_length();
    }
}

// Checks if the letter set extracted from the command line is valid.
void check_letter_set(Game* game)
{
    // Check all letters are alphabetical characters.
    for (int i = 0; i < game->lettersLength; i++) {
        if (isalpha(game->letters[i]) == 0) {
            exit_invalid_letter_set();
        }
    }
    // Check number of letters does not exceed the maximum length
    if (game->lettersLength > MAX_NUM_LETTERS) {
        exit_too_many_letters();
    }
    // Check number of letters does not exceed the minimum length
    if (game->lettersLength < game->minLength) {
        exit_not_enough_letters(game->minLength);
    }
}
