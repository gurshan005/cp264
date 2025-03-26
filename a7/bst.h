#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Record data for each node */
typedef struct record {
    char name[20];
    float score;
} RECORD;

/* Forward declaration of BST node */
typedef struct bstnode BSTNODE;

/* Definition of BST node */
struct bstnode {
    RECORD data;
    BSTNODE *left;
    BSTNODE *right;
};

/* Create a BST node with the given RECORD data.
 * Uses malloc() to allocate memory and returns the new node pointer.
 */
BSTNODE *bst_node(RECORD data);

/* Search the BST for a node whose data.name matches the given key.
 *
 * @param root - pointer to tree root.
 * @param key  - search key (string).
 *
 * @return pointer to the matched node if found, otherwise NULL.
 */
BSTNODE *bst_search(BSTNODE *root, char *key);

/* Insert a node with the given record data into the BST.
 *
 * @param rootp - pointer to pointer to tree root.
 * @param data  - record data for the new node.
 */
void bst_insert(BSTNODE **rootp, RECORD data);

/* Delete a node whose data.name matches the given key from the BST.
 *
 * @param rootp - pointer to pointer to tree root.
 * @param key   - key to match with data.name for deletion.
 */
void bst_delete(BSTNODE **rootp, char *key);

/* Clean the entire BST, freeing all nodes.
 *
 * @param rootp - pointer to pointer to tree root.
 */
void bst_clean(BSTNODE **rootp);

/* Extract and return (and remove) the smallest node (by data.name) from the BST.
 * The returned node will have its left/right pointers set to NULL.
 *
 * @param rootp - pointer to pointer to BST root.
 * @return pointer to the extracted smallest node, or NULL if tree is empty.
 */
BSTNODE *extract_smallest_node(BSTNODE **rootp);

#endif  /* BST_H */
