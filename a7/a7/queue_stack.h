#ifndef QUEUE_STACK_H
#define QUEUE_STACK_H

#include <stdlib.h>

/*---------- QUEUE ----------*/

typedef struct queue_node {
    void *data;
    struct queue_node *next;
} QueueNode;

typedef struct queue {
    QueueNode *front;
    QueueNode *rear;
} QUEUE;

/* Create and return a new empty queue. */
QUEUE *createQueue(void);

/* Enqueue an item to the queue. */
void enqueue(QUEUE *q, void *item);

/* Dequeue an item from the queue. Returns the item pointer, or NULL if empty. */
void *dequeue(QUEUE *q);

/* Check if the queue is empty. Returns non-zero if empty, zero otherwise. */
int isEmptyQueue(const QUEUE *q);

/* Free all memory associated with the queue. */
void freeQueue(QUEUE *q);

/*---------- STACK ----------*/

void freeQueue(QUEUE *q);




typedef struct stack_node {
    void *data;
    struct stack_node *next;
} StackNode;

typedef struct stack {
    StackNode *top;
} STACK;

/* Create and return a new empty stack. */
STACK *createStack(void);

/* Push an item onto the stack. */
void push(STACK *s, void *item);

/* Pop an item from the stack. Returns the item pointer, or NULL if empty. */
void *pop(STACK *s);

/* Check if the stack is empty. Returns non-zero if empty, zero otherwise. */
int isEmptyStack(const STACK *s);

/* Free all memory associated with the stack. */
void freeStack(STACK *s);

#endif // QUEUE_STACK_H
