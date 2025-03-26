// hash.h
#ifndef HASH_H
#define HASH_H

#define NAME_SIZE 20

// Data structure to store key-value pair.
typedef struct {
    char name[NAME_SIZE];
    int value;
} DATA;

// Node structure for chained hash table.
typedef struct hnode {
    DATA data;
    struct hnode *next;
} HNODE;

// Hashtable structure.
typedef struct hashtable {
    int size;
    int count;
    HNODE **hna;
} HASHTABLE;

// Function prototypes
int hash(char *key, int size);
HASHTABLE *new_hashtable(int size);
int hashtable_insert(HASHTABLE *ht, DATA data);
HNODE *hashtable_search(HASHTABLE *ht, char *name);
int hashtable_delete(HASHTABLE *ht, char *key);
void hashtable_clean(HASHTABLE **ht);

#endif


