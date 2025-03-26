#ifndef AVL_H
#define AVL_H

/* Record structure. */
typedef struct record {
    char name[20];
    float score;
} RECORD;

/* Forward declaration for AVL node. */
typedef struct avlnode AVLNODE;

/* AVL node structure. */
struct avlnode {
    RECORD data;
    int height;
    AVLNODE *left;
    AVLNODE *right;
};

/* 
 * Insert a node of given record data into AVL tree.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param data  - record data for the new node.
 */
void avl_insert(AVLNODE **rootp, RECORD data);

/* 
 * Delete a node of data.name matched with given key from AVL tree.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param key   - key to match with data.name for deletion.
 */
void avl_delete(AVLNODE **rootp, char *key);

/* 
 * Search AVL tree by key of the name field.
 *
 * @param root - pointer to tree root.
 * @param key  - key to match with data.name for search.
 * @return     - node pointer if found, otherwise NULL.
 */
AVLNODE *avl_search(AVLNODE *root, char *key);

/* 
 * Clean (free) the AVL tree.
 *
 * @param rootp - pointer of pointer to tree root.
 */
void avl_clean(AVLNODE **rootp);

/* 
 * Get the height of AVL tree.
 *
 * @param root - pointer to the root of tree.
 * @return     - the height value at root.
 */
int height(AVLNODE *root);

/* 
 * Return the balance factor at the given node.
 *
 * @param np - pointer to the node of tree.
 * @return   - the balance factor at the node.
 */
int balance_factor(AVLNODE *np);

/* 
 * Perform a left rotation at a given node.
 *
 * @param np - pointer to the rotation node.
 * @return   - the pointer to the new root of the rotated subtree.
 */
AVLNODE *rotate_left(AVLNODE *np);

/* 
 * Perform a right rotation at a given node.
 *
 * @param np - pointer to the rotation node.
 * @return   - the pointer to the new root of the rotated subtree.
 */
AVLNODE *rotate_right(AVLNODE *np);

#endif // AVL_H