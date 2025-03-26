#include "dllist.h"

/*
 * Create and return a new node using malloc() with the passed data value.
 */
NODE *dll_node(char value) {
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed in dll_node.\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

/*
 * Insert a given node at the beginning of a doubly linked list.
 */
void dll_insert_start(DLL *dllp, NODE *np) {
    if (dllp == NULL || np == NULL)
        return;
    
    np->prev = NULL;
    np->next = dllp->start;
    
    if (dllp->start != NULL) {
        dllp->start->prev = np;
    } else {
        // List is empty; new node is also the end.
        dllp->end = np;
    }
    
    dllp->start = np;
    dllp->length++;
}

/*
 * Insert a node at the end of a doubly linked list.
 */
void dll_insert_end(DLL *dllp, NODE *np) {
    if (dllp == NULL || np == NULL)
        return;
    
    np->next = NULL;
    np->prev = dllp->end;
    
    if (dllp->end != NULL) {
        dllp->end->next = np;
    } else {
        // List is empty; new node is also the start.
        dllp->start = np;
    }
    
    dllp->end = np;
    dllp->length++;
}

/*
 * Delete the first node of a doubly linked list.
 */
void dll_delete_start(DLL *dllp) {
    if (dllp == NULL || dllp->start == NULL)
        return;
    
    NODE *temp = dllp->start;
    dllp->start = temp->next;
    
    if (dllp->start != NULL) {
        dllp->start->prev = NULL;
    } else {
        // List becomes empty.
        dllp->end = NULL;
    }
    
    free(temp);
    dllp->length--;
}

/*
 * Delete the end node of a doubly linked list.
 */
void dll_delete_end(DLL *dllp) {
    if (dllp == NULL || dllp->end == NULL)
        return;
    
    NODE *temp = dllp->end;
    dllp->end = temp->prev;
    
    if (dllp->end != NULL) {
        dllp->end->next = NULL;
    } else {
        // List becomes empty.
        dllp->start = NULL;
    }
    
    free(temp);
    dllp->length--;
}

/*
 * Clean and free all nodes of a doubly linked list and reset the list.
 */
void dll_clean(DLL *dllp) {
    if (dllp == NULL)
        return;
    
    NODE *current = dllp->start;
    while (current != NULL) {
        NODE *temp = current;
        current = current->next;
        free(temp);
    }
    
    dllp->start = NULL;
    dllp->end = NULL;
    dllp->length = 0;
}
