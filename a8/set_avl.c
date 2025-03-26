#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set_avl.h"

/* 
 * Create and return an empty set.
 */
SET *set_create(void) {
    SET *s = malloc(sizeof(SET));
    if (s != NULL) {
        s->root = NULL;
        s->count = 0;
    }
    return s;
}

/* 
 * Returns the number of elements in the set.
 */
int set_size(SET *s) {
    if (s == NULL)
        return 0;
    return s->count;
}

/* 
 * Returns 1 if set s contains element e; otherwise 0.
 */
int set_contain(SET *s, char *e) {
    if (s == NULL)
        return 0;
    /* 
     * avl_search uses the key (string) to match the name field in the RECORD.
     * It returns a pointer to the node if found, or NULL otherwise.
     */
    AVLNODE *node = avl_search(s->root, e);
    return (node != NULL) ? 1 : 0;
}

/* 
 * Add element e into set s.
 *
 * The function creates a RECORD with the string stored in the name field (score is set to 0)
 * and inserts it into the AVL tree. Duplicates are not inserted.
 */
void set_add(SET *s, char *e) {
    if (s == NULL)
        return;
    if (set_contain(s, e))
        return; // Already exists, do not insert duplicate

    RECORD rec;
    /* Copy e into rec.name (up to 19 characters) and ensure null-termination */
    strncpy(rec.name, e, sizeof(rec.name) - 1);
    rec.name[sizeof(rec.name) - 1] = '\0';
    rec.score = 0.0f;
    
    avl_insert(&(s->root), rec);
    s->count++;
}

/* 
 * Remove element e from set s.
 *
 * Uses avl_delete which matches the key (string) with data.name in the AVL tree.
 */
void set_remove(SET *s, char *e) {
    if (s == NULL)
        return;
    if (!set_contain(s, e))
        return;  // Element not found; nothing to remove
    avl_delete(&(s->root), e);
    s->count--;
}

/* 
 * Clear the set by cleaning the underlying AVL tree and resetting the count.
 */
void set_clean(SET *s) {
    if (s == NULL)
        return;
    avl_clean(&(s->root));
    s->count = 0;
}