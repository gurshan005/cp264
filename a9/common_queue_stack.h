#ifndef COMMON_QUEUE_STACK_H
#define COMMON_QUEUE_STACK_H

#define MAX_SIZE 100

// Stack structure
typedef struct {
    char items[MAX_SIZE][32];
    int top;
} STACK;

// Queue structure
typedef struct {
    char items[MAX_SIZE][32];
    int front, rear, count;
} QUEUE;

// Stack functions
void push(STACK *s, char *item);
char *pop(STACK *s);
char *peek(STACK *s);
int is_stack_empty(STACK *s);

// Queue functions
void enqueue(QUEUE *q, char *item);
char *dequeue(QUEUE *q);
int is_queue_empty(QUEUE *q);

#endif
