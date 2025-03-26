#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

/* Helper: return maximum of two integers */
static int max(int a, int b) {
    return (a > b) ? a : b;
}

/* 
 * Get the height of the AVL tree.
 * @param root - pointer to the root of tree.
 * @return     - height value (0 if node is NULL).
 */
int height(AVLNODE *root) {
    return (root == NULL) ? 0 : root->height;
}

/* 
 * Return the balance factor of the given node.
 * @param np - pointer to the node.
 * @return   - height(left subtree) - height(right subtree).
 */
int balance_factor(AVLNODE *np) {
    if (np == NULL)
        return 0;
    return height(np->left) - height(np->right);
}

/* 
 * Left rotation: rotates the subtree rooted at np to the left.
 */
AVLNODE *rotate_left(AVLNODE *np) {
    if (np == NULL || np->right == NULL)
        return np;
    AVLNODE *y = np->right;
    np->right = y->left;
    y->left = np;
    np->height = max(height(np->left), height(np->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

/* 
 * Right rotation: rotates the subtree rooted at np to the right.
 */
AVLNODE *rotate_right(AVLNODE *np) {
    if (np == NULL || np->left == NULL)
        return np;
    AVLNODE *x = np->left;
    np->left = x->right;
    x->right = np;
    np->height = max(height(np->left), height(np->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

/* 
 * Recursive helper for AVL insertion.
 */
static AVLNODE *avl_insert_rec(AVLNODE *node, RECORD data) {
    if (node == NULL) {
        AVLNODE *new_node = malloc(sizeof(AVLNODE));
        if (new_node == NULL)
            return NULL;
        new_node->data = data;  // structure copy
        new_node->height = 1;
        new_node->left = new_node->right = NULL;
        return new_node;
    }
    
    int cmp = strcmp(data.name, node->data.name);
    if (cmp < 0)
        node->left = avl_insert_rec(node->left, data);
    else if (cmp > 0)
        node->right = avl_insert_rec(node->right, data);
    else
        return node;  // duplicate keys not allowed; could update data if needed

    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = balance_factor(node);

    // Left Left Case
    if (balance > 1 && strcmp(data.name, node->left->data.name) < 0)
        return rotate_right(node);
    // Right Right Case
    if (balance < -1 && strcmp(data.name, node->right->data.name) > 0)
        return rotate_left(node);
    // Left Right Case
    if (balance > 1 && strcmp(data.name, node->left->data.name) > 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    // Right Left Case
    if (balance < -1 && strcmp(data.name, node->right->data.name) < 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

/* 
 * Insert a node of given record data into the AVL tree.
 * @param rootp - pointer to pointer to tree root.
 * @param data  - record data for the new node.
 */
void avl_insert(AVLNODE **rootp, RECORD data) {
    *rootp = avl_insert_rec(*rootp, data);
}

/* 
 * Helper: Find the node with minimum key in a subtree.
 */
static AVLNODE *min_value_node(AVLNODE *node) {
    AVLNODE *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

/* 
 * Recursive helper for AVL deletion.
 */
static AVLNODE *avl_delete_rec(AVLNODE *node, char *key) {
    if (node == NULL)
        return node;
    
    int cmp = strcmp(key, node->data.name);
    if (cmp < 0)
        node->left = avl_delete_rec(node->left, key);
    else if (cmp > 0)
        node->right = avl_delete_rec(node->right, key);
    else {
        // Node found.
        if (node->left == NULL || node->right == NULL) {
            AVLNODE *temp = node->left ? node->left : node->right;
            if (temp == NULL) {  // No child case
                temp = node;
                node = NULL;
            } else {
                // One child: copy the non-null child's data into node.
                *node = *temp;
            }
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            AVLNODE *temp = min_value_node(node->right);
            node->data = temp->data;  // Copy successor's data (structure copy)
            node->right = avl_delete_rec(node->right, temp->data.name);
        }
    }
    
    if (node == NULL)
        return node;
    
    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = balance_factor(node);
    
    // Left Left Case
    if (balance > 1 && balance_factor(node->left) >= 0)
        return rotate_right(node);
    // Left Right Case
    if (balance > 1 && balance_factor(node->left) < 0) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    // Right Right Case
    if (balance < -1 && balance_factor(node->right) <= 0)
        return rotate_left(node);
    // Right Left Case
    if (balance < -1 && balance_factor(node->right) > 0) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

/* 
 * Delete a node whose data.name matches key from the AVL tree.
 * @param rootp - pointer to pointer to tree root.
 * @param key   - key to match with data.name for deletion.
 */
void avl_delete(AVLNODE **rootp, char *key) {
    *rootp = avl_delete_rec(*rootp, key);
}

/* 
 * Search the AVL tree by key (data.name).
 * @param root - pointer to tree root.
 * @param key  - key to match with data.name.
 * @return     - pointer to node if found; otherwise NULL.
 */
AVLNODE *avl_search(AVLNODE *root, char *key) {
    if (root == NULL)
        return NULL;
    int cmp = strcmp(key, root->data.name);
    if (cmp == 0)
        return root;
    else if (cmp < 0)
        return avl_search(root->left, key);
    else
        return avl_search(root->right, key);
}

/* 
 * Helper: Recursively free nodes in the AVL tree.
 */
static void avl_clean_rec(AVLNODE *node) {
    if (node == NULL)
        return;
    avl_clean_rec(node->left);
    avl_clean_rec(node->right);
    free(node);
}

/* 
 * Clean (free) the AVL tree.
 * @param rootp - pointer to pointer to tree root.
 */
void avl_clean(AVLNODE **rootp) {
    avl_clean_rec(*rootp);
    *rootp = NULL;
}