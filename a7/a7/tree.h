#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

/* Define node structure of a binary tree
 * data  - data field of tree node
 * left  - pointer to the left child
 * right - pointer to the right child
 */
typedef struct tnode {
    char data;
    struct tnode *left;
    struct tnode *right;
} TNODE;

/* Define a structure to represent tree properties. 
 * order  - the number of nodes 
 * height - the height of the tree
 */
typedef struct tree_props {
    int order;
    int height;
} TPROPS;

/* Compute and return the TPROPS value of a tree.
 * @param root - pointer to the root of a tree
 * @return - TPROPS structure with the number of nodes and the height
 */
TPROPS tree_property(TNODE *root);

/* Display the node data of the tree in pre-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */
void preorder(TNODE *root);

/* Display the node data of the tree in in-order and format "%c".
 *
 *  @param root - pointer to the root of a tree
 */
void inorder(TNODE *root);

/* Display the node data of the tree in post-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */
void postorder(TNODE *root);

/* Display the node data of the tree in breadth-first-order and format "%c ".
 * Required to use auxiliary queue and an iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 */
void bforder(TNODE *root);

/* Search by key using breadth-first-search algorithm.
 * Required to use auxiliary queue and an iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key  - search key (character)
 *
 *  @return - pointer to the found node if found, otherwise NULL
 */
TNODE *bfs(TNODE *root, char key);

/* Search by key using depth-first-search algorithm.
 * Required to use auxiliary stack and an iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key  - search key (character)
 *
 *  @return - pointer to the found node if found, otherwise NULL
 */
TNODE *dfs(TNODE *root, char key);

/* Create a TNODE node, set its data to val, and return the pointer.
 * Uses malloc() to allocate memory.
 */
TNODE *tree_node(char val);

/* Clean a tree by freeing all nodes.
 * @param rootp - pointer to pointer to the tree root
 */
void clean_tree(TNODE **rootp);

/* Create a new node with the given value and insert it into the tree 
 * at the first available position in breadth-first order (left to right).
 *
 * @param rootp - pointer to pointer to the tree root
 * @param val   - data for the new node
 */
void insert_tree(TNODE **rootp, char val);

#endif // TREE_H
