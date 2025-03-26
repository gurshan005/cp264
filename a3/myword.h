#ifndef MYWORD_H
#define MYWORD_H

#include <stdio.h>

#define MAX_WORD_LEN 20       // Maximum length of a word
#define MAX_DICT_SIZE 4096    // Maximum size for dictionary storage (increased to hold all stop words)
#define MAX_WORDS 5000        // Maximum number of distinct keywords
#define MAX_LINE_LEN 1000     // Maximum length of a line from the input text

// Define enumeration type BOOLEAN with FALSE=0 and TRUE=1.
typedef enum { FALSE = 0, TRUE = 1 } BOOLEAN;

// Define structure type WORD to store a keyword and its frequency.
typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WORD;

// Define structure type WORDSTATS to hold overall text statistics.
typedef struct {
    int line_count;    // Number of lines in the file
    int word_count;    // Total number of words in the file
    int keyword_count; // Number of distinct non-common (non-stop) words
} WORDSTATS;

/*
 * Load stop-word data from file into a dictionary.
 * The dictionary is stored in a char array as a sequence of stop words,
 * each delimited by a leading and trailing space (e.g., " word1 word2 word3 ").
 *
 * @param fp - FILE pointer to an opened stop-word file.
 * @param dictionary - char array where the dictionary is stored.
 * @return - the number of words added to the dictionary.
 */
int create_dictionary(FILE *fp, char *dictionary);

/*
 * Determine if a given word is contained in the given dictionary.
 *
 * @param dictionary - char pointer to a char array containing the dictionary.
 * @param word - pointer to the word to search for.
 * @return - TRUE if the word is found, FALSE otherwise.
 */
BOOLEAN contain_word(char *dictionary, char *word);

/*
 * Process text data from a file to compute word statistics:
 * number of lines, total words, and distinct keywords (non-stop words)
 * along with each keyword's frequency.
 *
 * @param fp - FILE pointer to the input text file.
 * @param words - WORD array to hold keywords and their frequencies.
 * @param dictionary - the stop-word dictionary.
 * @return - a WORDSTATS structure with the computed statistics.
 */
WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary);

#endif /* MYWORD_H */
