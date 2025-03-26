#include "myrecord_sllist.h"

/**
 * Searches the singly linked list for a node whose record name matches the given key.
 *
 * @param sllp - pointer to the singly linked list structure.
 * @param name - the key to search for.
 * @return Pointer to the found node if present; otherwise NULL.
 */
NODE *sll_search(SLL *sllp, char *name) {
    if (sllp == NULL || sllp->start == NULL || name == NULL) {
        return NULL;
    }
    
    NODE *current = sllp->start;
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/**
 * Inserts a new record into the singly linked list while keeping the list sorted by the record name.
 *
 * @param sllp - pointer to the singly linked list structure.
 * @param name - name field of the new record.
 * @param score - the score of the new record.
 */
void sll_insert(SLL *sllp, char *name, float score) {
    if (sllp == NULL || name == NULL) {
        return;
    }
    
    // Create a new node.
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE); // Alternatively, handle error as needed.
    }
    
    // Copy the name safely (ensure null termination) and set the score.
    strncpy(new_node->data.name, name, sizeof(new_node->data.name) - 1);
    new_node->data.name[sizeof(new_node->data.name) - 1] = '\0';
    new_node->data.score = score;
    new_node->next = NULL;
    
    // Insert at the beginning if list is empty or new node should come before the first node.
    if (sllp->start == NULL || strcmp(new_node->data.name, sllp->start->data.name) < 0) {
        new_node->next = sllp->start;
        sllp->start = new_node;
        sllp->length++;
        return;
    }
    
    // Otherwise, traverse to find the correct sorted position.
    NODE *current = sllp->start;
    while (current->next != NULL && strcmp(current->next->data.name, new_node->data.name) < 0) {
        current = current->next;
    }
    
    // Insert the new node.
    new_node->next = current->next;
    current->next = new_node;
    sllp->length++;
}

/**
 * Deletes the node from the singly linked list whose record name matches the given key.
 *
 * @param sllp - pointer to the singly linked list structure.
 * @param name - the key used to find the node for deletion.
 * @return 1 if a node was deleted; 0 otherwise.
 */
int sll_delete(SLL *sllp, char *name) {
    if (sllp == NULL || sllp->start == NULL || name == NULL) {
        return 0;
    }
    
    NODE *current = sllp->start;
    NODE *prev = NULL;
    
    // Traverse the list looking for a matching node.
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            // Node found; adjust pointers to remove it.
            if (prev == NULL) { // The node to delete is the first node.
                sllp->start = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            sllp->length--;
            return 1;
        }
        prev = current;
        current = current->next;
    }
    
    // No matching node found.
    return 0;
}

/**
 * Deletes all nodes in the singly linked list and resets its length.
 *
 * @param sllp - pointer to the singly linked list structure.
 */
void sll_clean(SLL *sllp) {
    if (sllp == NULL) {
        return;
    }
    
    NODE *current = sllp->start;
    while (current != NULL) {
        NODE *temp = current;
        current = current->next;
        free(temp);
    }
    
    sllp->start = NULL;
    sllp->length = 0;
}
