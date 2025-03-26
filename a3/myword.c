#include "myword.h"
#include "mystring.h"  // For str_lower() and str_trim()
#include <string.h>
#include <stdio.h>

/*
 * create_dictionary()
 * -------------------
 * Reads the stop-word file line by line and tokenizes each line.
 * Each token (stop word) is converted to lowercase and, if not already
 * in the dictionary, is appended (with a leading and trailing space for
 * exact matching). We call fseek() to ensure the file pointer is at the beginning.
 */
int create_dictionary(FILE *fp, char *dictionary) {
    char line[MAX_LINE_LEN];
    int word_count = 0;
    
    if (!fp || !dictionary) {
        printf("Error: Null file pointer or dictionary buffer\n");
        return 0;
    }
    
    // Ensure we start at the beginning of the file.
    fseek(fp, 0, SEEK_SET);
    
    // Initialize the dictionary as an empty string.
    dictionary[0] = '\0';
    
    // Read each line from the file.
    while (fgets(line, sizeof(line), fp)) {
        // Tokenize the line using whitespace as delimiters.
        char *token = strtok(line, " \t\n\r");
        while (token != NULL) {
            // Convert the token to lowercase.
            str_lower(token);
            // If the word is not already in the dictionary, add it.
            if (!contain_word(dictionary, token)) {
                if (strlen(dictionary) + strlen(token) + 3 >= MAX_DICT_SIZE) {
                    printf("Warning: Dictionary buffer full, truncating.\n");
                    return word_count;
                }
                strcat(dictionary, " ");  // Leading space for exact matching
                strcat(dictionary, token);
                strcat(dictionary, " ");  // Trailing space
                word_count++;
            }
            token = strtok(NULL, " \t\n\r");
        }
    }
    
    return word_count;
}

/*
 * contain_word()
 * --------------
 * Checks whether a given word appears in the dictionary.
 * It constructs a search string with leading and trailing spaces and
 * uses strstr() for an exact match.
 */
BOOLEAN contain_word(char *dictionary, char *word) {
    if (!dictionary || !word)
        return FALSE;
    
    char search_word[MAX_WORD_LEN + 3]; // Buffer for " word "
    snprintf(search_word, sizeof(search_word), " %s ", word);
    
    return (strstr(dictionary, search_word) != NULL) ? TRUE : FALSE;
}

/*
 * process_words()
 * ---------------
 * Reads the input text file line by line, trims and lowercases the line,
 * tokenizes it into words, and:
 *   - Increments the total word count.
 *   - For tokens that are not stop words, adds them (or updates their frequency)
 *     in the keyword array.
 */
WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary) {
    WORDSTATS stats = {0, 0, 0};
    char line[MAX_LINE_LEN];
    char *token;
    
    if (!fp || !words || !dictionary) {
        printf("Error: Null pointer detected in process_words\n");
        return stats;
    }
    
    while (fgets(line, sizeof(line), fp)) {
        stats.line_count++;
        str_trim(line);  // Remove extra spaces
        str_lower(line); // Convert the entire line to lowercase
        
        // Tokenize the line using common delimiters.
        token = strtok(line, " ,.\t\n");
        while (token != NULL) {
            stats.word_count++;
            
            // Only process the token if it is not a stop word.
            if (!contain_word(dictionary, token)) {
                int found = FALSE;
                // Check if the token is already present in the keywords array.
                for (int i = 0; i < stats.keyword_count; i++) {
                    if (strcmp(words[i].word, token) == 0) {
                        words[i].count++;
                        found = TRUE;
                        break;
                    }
                }
                // If the token is new and there is space in the array, add it.
                if (!found && stats.keyword_count < MAX_WORDS) {
                    strncpy(words[stats.keyword_count].word, token, MAX_WORD_LEN - 1);
                    words[stats.keyword_count].word[MAX_WORD_LEN - 1] = '\0';
                    words[stats.keyword_count].count = 1;
                    stats.keyword_count++;
                }
            }
            token = strtok(NULL, " ,.\t\n");
        }
    }
    
    return stats;
}
