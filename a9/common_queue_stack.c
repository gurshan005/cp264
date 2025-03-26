#include "common_queue_stack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Stack implementations
void push(STACK *s, char *item) {
    if (s->top < MAX_SIZE - 1)
        strcpy(s->items[++(s->top)], item);
    else
        printf("Stack overflow!\n");
}

char *pop(STACK *s) {
    if (s->top >= 0)
        return s->items[(s->top)--];
    printf("Stack underflow!\n");
    return NULL;
}

char *peek(STACK *s) {
    if (s->top >= 0)
        return s->items[s->top];
    return NULL;
}

int is_stack_empty(STACK *s) {
    return s->top == -1;
}

// Queue implementations
void enqueue(QUEUE *q, char *item) {
    if (q->count < MAX_SIZE) {
        strcpy(q->items[q->rear], item);
        q->rear = (q->rear + 1) % MAX_SIZE;
        q->count++;
    } else {
        printf("Queue overflow!\n");
    }
}

char *dequeue(QUEUE *q) {
    if (q->count > 0) {
        char *item = q->items[q->front];
        q->front = (q->front + 1) % MAX_SIZE;
        q->count--;
        return item;
    }
    printf("Queue underflow!\n");
    return NULL;
}

int is_queue_empty(QUEUE *q) {
    return q->count == 0;
}
