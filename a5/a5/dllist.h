#ifndef DLLIST_H
#define DLLIST_H

#include <stdio.h>
#include <stdlib.h>

/*
 * Define node structure NODE of a doubly linked list to hold a char data value.
 */
typedef struct node {
    char data;
    struct node *prev;
    struct node *next;
} NODE;

/* 
 * Define a structure DLL to hold the length, start and end node addresses of a doubly linked list.
 */
typedef struct dll {
    int length;
    NODE *start;
    NODE *end;
} DLL;

/*
 * Create and return a new node using malloc() with passed data value and returns pointer of the node.
 */
NODE *dll_node(char value);

/*
 * Insert a given node at the beginning of a doubly linked list.
 * @param dllp - reference to input DLL variable 
 * @param np   - reference of a NODE node to be inserted
 */
void dll_insert_start(DLL *dllp, NODE *np);

/*
 * Insert a node at the end of a doubly linked list.
 * @param dllp - reference to input DLL variable 
 * @param np   - reference of a NODE node to be inserted
 */
void dll_insert_end(DLL *dllp, NODE *np);

/*
 * Delete the first node of a doubly linked list.
 * @param dllp - reference to input DLL variable 
 */
void dll_delete_start(DLL *dllp);

/*
 * Delete the end node of a doubly linked list.
 * @param dllp - reference to input DLL variable  
 */
void dll_delete_end(DLL *dllp);

/*
 * Clean and free the nodes of a doubly linked list and reset start and length.
 * @param dllp - reference to input DLL variable 
 */
void dll_clean(DLL *dllp);

#endif
