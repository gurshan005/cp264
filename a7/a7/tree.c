#include "tree.h"
#include "queue_stack.h"  

/*----------------------------------------------------
  TREE PROPERTIES AND RECURSIVE TRAVERSALS
----------------------------------------------------*/

// Compute tree properties (number of nodes and height)
TPROPS tree_property(TNODE *root) {
    TPROPS props = {0, 0};
    if (root == NULL)
        return props;
    
    TPROPS leftProps = tree_property(root->left);
    TPROPS rightProps = tree_property(root->right);
    
    props.order = leftProps.order + rightProps.order + 1;
    props.height = (leftProps.height > rightProps.height ? leftProps.height : rightProps.height) + 1;
    return props;
}

// Pre-order traversal: Visit root, then left, then right.
void preorder(TNODE *root) {
    if (root == NULL)
        return;
    printf("%c ", root->data);
    preorder(root->left);
    preorder(root->right);
}

// In-order traversal: Visit left, then root, then right.
void inorder(TNODE *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%c", root->data);
    inorder(root->right);
}

// Post-order traversal: Visit left, then right, then root.
void postorder(TNODE *root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%c ", root->data);
}

/*----------------------------------------------------
  ITERATIVE BREADTH-FIRST TRAVERSAL AND SEARCH
----------------------------------------------------*/

// bforder: Print tree nodes in breadth-first order using a queue.
void bforder(TNODE *root) {
    if (root == NULL)
        return;
    
    QUEUE *q = createQueue();
    enqueue(q, (void *)root);
    
    while (!isEmptyQueue(q)) {
        TNODE *node = (TNODE *)dequeue(q);
        printf("%c ", node->data);
        if (node->left != NULL)
            enqueue(q, (void *)node->left);
        if (node->right != NULL)
            enqueue(q, (void *)node->right);
    }
    freeQueue(q);
}
// bfs: Search for a node with key using breadth-first search.
TNODE *bfs(TNODE *root, char key) {
    if (root == NULL)
        return NULL;
    
    QUEUE *q = createQueue();
    enqueue(q, (void *)root);
    
    while (!isEmptyQueue(q)) {
        TNODE *node = (TNODE *)dequeue(q);
        if (node->data == key) {
            freeQueue(q);
            return node;
        }
        if (node->left != NULL)
            enqueue(q, (void *)node->left);
        if (node->right != NULL)
            enqueue(q, (void *)node->right);
    }
    freeQueue(q);
    return NULL;
}

/*----------------------------------------------------
  ITERATIVE DEPTH-FIRST SEARCH
----------------------------------------------------*/

// dfs: Search for a node with key using depth-first search (iterative with a stack).
TNODE *dfs(TNODE *root, char key) {
    if (root == NULL)
        return NULL;
    
    STACK *s = createStack();
    push(s, (void *)root);
    
    while (!isEmptyStack(s)) {
        TNODE *node = (TNODE *)pop(s);
        if (node->data == key) {
            freeStack(s);
            return node;
        }
        // Push right child first so that left child is processed first.
        if (node->right != NULL)
            push(s, (void *)node->right);
        if (node->left != NULL)
            push(s, (void *)node->left);
    }
    freeStack(s);
    return NULL;
}

/*----------------------------------------------------
  NODE CREATION, CLEANUP, AND INSERTION
----------------------------------------------------*/

// tree_node: Create a new tree node with the specified value.
TNODE *tree_node(char val) {
    TNODE *node = (TNODE *)malloc(sizeof(TNODE));
    if (node != NULL) {
        node->data = val;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

// clean_tree: Recursively free all nodes in the tree.
void clean_tree(TNODE **rootp) {
    if (rootp == NULL || *rootp == NULL)
        return;
    
    clean_tree(&((*rootp)->left));
    clean_tree(&((*rootp)->right));
    free(*rootp);
    *rootp = NULL;
}

// insert_tree: Insert a new node with the given value at the first available position
// (level order, left to right) using a queue.
void insert_tree(TNODE **rootp, char val) {
    TNODE *new_node = tree_node(val);
    if (*rootp == NULL) {
        *rootp = new_node;
        return;
    }
    
    QUEUE *q = createQueue();
    enqueue(q, (void *)*rootp);
    
    while (!isEmptyQueue(q)) {
        TNODE *node = (TNODE *)dequeue(q);
        if (node->left == NULL) {
            node->left = new_node;
            freeQueue(q);
            return;
        } else {
            enqueue(q, (void *)node->left);
        }
        if (node->right == NULL) {
            node->right = new_node;
            freeQueue(q);
            return;
        } else {
            enqueue(q, (void *)node->right);
        }
    }
    freeQueue(q);
}
