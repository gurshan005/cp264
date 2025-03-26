// hash.c
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hash function implementation
int hash(char *key, int size) {
    int sum = 0;
    while (*key) {
        sum += (int)(*key);
        key++;
    }
    return sum % size;
}

// Create a new hash table
HASHTABLE *new_hashtable(int size) {
    HASHTABLE *ht = (HASHTABLE *)malloc(sizeof(HASHTABLE));
    ht->size = size;
    ht->count = 0;
    ht->hna = (HNODE **)malloc(size * sizeof(HNODE *));
    for (int i = 0; i < size; i++) {
        ht->hna[i] = NULL;
    }
    return ht;
}

// Insert data into the hash table
int hashtable_insert(HASHTABLE *ht, DATA data) {
    int index = hash(data.name, ht->size);
    HNODE *node = ht->hna[index];

    while (node) {
        if (strcmp(node->data.name, data.name) == 0) {
            node->data.value = data.value; // Update existing value
            return 0;
        }
        node = node->next;
    }

    HNODE *new_node = (HNODE *)malloc(sizeof(HNODE));
    new_node->data = data;
    new_node->next = ht->hna[index];
    ht->hna[index] = new_node;
    ht->count++;

    return 1;
}

// Search the hash table
HNODE *hashtable_search(HASHTABLE *ht, char *name) {
    int index = hash(name, ht->size);
    HNODE *node = ht->hna[index];

    while (node) {
        if (strcmp(node->data.name, name) == 0)
            return node;
        node = node->next;
    }

    return NULL;
}

// Delete an entry from the hash table
int hashtable_delete(HASHTABLE *ht, char *key) {
    int index = hash(key, ht->size);
    HNODE *node = ht->hna[index];
    HNODE *prev = NULL;

    while (node) {
        if (strcmp(node->data.name, key) == 0) {
            if (prev == NULL)
                ht->hna[index] = node->next;
            else
                prev->next = node->next;

            free(node);
            ht->count--;
            return 1;
        }
        prev = node;
        node = node->next;
    }

    return 0;
}

// Clean up the entire hash table
void hashtable_clean(HASHTABLE **ht) {
    HNODE *current, *temp;
    for (int i = 0; i < (*ht)->size; i++) {
        current = (*ht)->hna[i];
        while (current) {
            temp = current;
            current = current->next;
            free(temp);
        }
    }
    free((*ht)->hna);
    free(*ht);
    *ht = NULL;
}