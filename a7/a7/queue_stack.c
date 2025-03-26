#include "queue_stack.h"

/*---------- QUEUE IMPLEMENTATION ----------*/

QUEUE *createQueue(void) {
    QUEUE *q = malloc(sizeof(QUEUE));
    if (q) {
        q->front = q->rear = NULL;
    }
    return q;
}

void enqueue(QUEUE *q, void *item) {
    if (!q)
        return;
    QueueNode *newNode = malloc(sizeof(QueueNode));
    if (!newNode)
        return;
    newNode->data = item;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void *dequeue(QUEUE *q) {
    if (!q || q->front == NULL)
        return NULL;
    QueueNode *temp = q->front;
    void *data = temp->data;
    q->front = temp->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return data;
}

int isEmptyQueue(const QUEUE *q) {
    return (q == NULL || q->front == NULL);
}

void freeQueue(QUEUE *q) {
    if (!q)
        return;
    while (!isEmptyQueue(q)) {
        dequeue(q);
    }
    free(q);
}

/*---------- STACK IMPLEMENTATION ----------*/

STACK *createStack(void) {
    STACK *s = malloc(sizeof(STACK));
    if (s) {
        s->top = NULL;
    }
    return s;
}

void push(STACK *s, void *item) {
    if (!s)
        return;
    StackNode *newNode = malloc(sizeof(StackNode));
    if (!newNode)
        return;
    newNode->data = item;
    newNode->next = s->top;
    s->top = newNode;
}

void *pop(STACK *s) {
    if (!s || s->top == NULL)
        return NULL;
    StackNode *temp = s->top;
    void *data = temp->data;
    s->top = temp->next;
    free(temp);
    return data;
}

int isEmptyStack(const STACK *s) {
    return (s == NULL || s->top == NULL);
}

void freeStack(STACK *s) {
    if (!s)
        return;
    while (!isEmptyStack(s)) {
        pop(s);
    }
    free(s);
}


