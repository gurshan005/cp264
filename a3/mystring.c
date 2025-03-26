#include "mystring.h"

int str_words(char *s) {
    int count = 0, in_word = 0;
    while (*s) {
        if ((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z')) {
            if (!in_word) {
                count++;
                in_word = 1;
            }
        } else if (*s == ' ' || *s == '\t' || *s == ',' || *s == '.') {
            in_word = 0;
        }
        s++;
    }
    return count;
}

int str_lower(char *s) {
    int count = 0;
    while (*s) {
        if (*s >= 'A' && *s <= 'Z') {
            *s = *s + ('a' - 'A');  // Convert uppercase to lowercase
            count++;
        }
        s++;
    }
    return count;
}



void str_trim(char *s) {
    char *read = s, *write = s;
    while (*read == ' ') read++; 

    int spaceEncountered = 0;
    while (*read) {
        if (*read == ' ') {
            if (!spaceEncountered) {
                *write++ = ' ';
                spaceEncountered = 1;
            }
        } else {
            *write++ = *read;
            spaceEncountered = 0;
        }
        read++;
    }
    if (write > s && *(write - 1) == ' ') write--; 
    *write = '\0';
}
