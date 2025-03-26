#ifndef SET_AVL_H
#define SET_AVL_H

#include "avl.h"  // Uses AVLNODE and functions from avl.h

/* SET structure representing a set of strings, built upon an AVL tree */
typedef struct set {
    AVLNODE *root;  /* Root of the AVL tree */
    int count;      /* Number of elements in the set */
} SET;

/**
 * Create and return an empty set.
 *
 * @return pointer to an initialized empty set.
 */
SET *set_create(void);

/**
 * Returns the number of elements in the set.
 *
 * @param s - pointer to the set.
 * @return number of elements.
 */
int set_size(SET *s);

/**
 * Returns 1 if set s contains element e; otherwise 0.
 *
 * @param s - pointer to the set.
 * @param e - string element to search for.
 * @return 1 if found, 0 if not.
 */
int set_contain(SET *s, char *e);

/**
 * Add element e into set s.
 *
 * @param s - pointer to the set.
 * @param e - string element to add.
 */
void set_add(SET *s, char *e);

/**
 * Remove element e from set s.
 *
 * @param s - pointer to the set.
 * @param e - string element to remove.
 */
void set_remove(SET *s, char *e);

/**
 * Clear the set by cleaning the underlying AVL tree and resetting its fields.
 *
 * @param s - pointer to the set.
 */
void set_clean(SET *s);

#endif // SET_AVL_H