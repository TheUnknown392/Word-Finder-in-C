#ifndef QUEUE_IMPLEMENTATION
#define QUEUE_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>

#define MAX 64

struct que{
    long array[MAX];
    int front;
    int rear;
};

int enqueue(struct que *queue, long n);
long dequeue(struct que *queue);
void innitQueue(struct que * queue);
int isfull(struct que * queue);
int isempty(struct que * queue);
#endif