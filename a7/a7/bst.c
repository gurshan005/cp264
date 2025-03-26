#include "bst.h"

/* Create a BST node with the given RECORD data */
BSTNODE *bst_node(RECORD data) {
    BSTNODE *node = malloc(sizeof(BSTNODE));
    if (node == NULL)
        return NULL;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/* Search the BST recursively by comparing key with data.name */
BSTNODE *bst_search(BSTNODE *root, char *key) {
    if (root == NULL)
        return NULL;
    
    int cmp = strcmp(key, root->data.name);
    if (cmp == 0)
        return root;
    else if (cmp < 0)
        return bst_search(root->left, key);
    else
        return bst_search(root->right, key);
}

/* Insert a new node with the given RECORD data into the BST */
void bst_insert(BSTNODE **rootp, RECORD data) {
    if (*rootp == NULL) {
        *rootp = bst_node(data);
        return;
    }
    int cmp = strcmp(data.name, (*rootp)->data.name);
    if (cmp < 0)
        bst_insert(&((*rootp)->left), data);
    else if (cmp > 0)
        bst_insert(&((*rootp)->right), data);
    else {
        /* Duplicate key: update the score or do nothing.
         * Here we choose to update the score.
         */
        (*rootp)->data.score = data.score;
    }
}

/* Delete a node with a matching key from the BST */
void bst_delete(BSTNODE **rootp, char *key) {
    if (*rootp == NULL)
        return;
    
    int cmp = strcmp(key, (*rootp)->data.name);
    
    if (cmp < 0)
        bst_delete(&((*rootp)->left), key);
    else if (cmp > 0)
        bst_delete(&((*rootp)->right), key);
    else {
        /* Found the node to delete */
        BSTNODE *temp;
        if ((*rootp)->left == NULL) {
            temp = *rootp;
            *rootp = (*rootp)->right;
            free(temp);
        } else if ((*rootp)->right == NULL) {
            temp = *rootp;
            *rootp = (*rootp)->left;
            free(temp);
        } else {
            /* Node has two children.
             * Replace its data with the smallest node in the right subtree.
             */
            BSTNODE *smallest = extract_smallest_node(&((*rootp)->right));
            /* Copy the data from the smallest node */
            (*rootp)->data = smallest->data;
            free(smallest);
        }
    }
}

/* Clean the BST by recursively freeing all nodes */
void bst_clean(BSTNODE **rootp) {
    if (rootp == NULL || *rootp == NULL)
        return;
    bst_clean(&((*rootp)->left));
    bst_clean(&((*rootp)->right));
    free(*rootp);
    *rootp = NULL;
}

/* Extract and remove the smallest node from the BST.
 * The smallest node is the leftmost node in the tree.
 */
BSTNODE *extract_smallest_node(BSTNODE **rootp) {
    if (rootp == NULL || *rootp == NULL)
        return NULL;
    
    if ((*rootp)->left == NULL) {
        BSTNODE *smallest = *rootp;
        /* Attach the right subtree in place of the smallest node */
        *rootp = (*rootp)->right;
        smallest->right = NULL;  /* disconnect any child */
        return smallest;
    } else {
        return extract_smallest_node(&((*rootp)->left));
    }
}

