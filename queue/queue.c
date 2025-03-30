#include "queue.h"

int enqueue(struct que *queue, long n){

    if ((queue->rear + 1) % MAX == queue->front) {
        return -1;  // Queue is full
    }

    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->rear = (queue->rear + 1) % MAX;
    queue->array[queue->rear] = n;
    return 0;  
}

long dequeue(struct que *queue){
    if (isempty(queue)) {
        return -1;  // Queue is empty
    }
    long n = queue->array[queue->front];

    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % MAX;
    }

    return n;
}

void innitQueue(struct que *queue){
    queue->front = -1;
    queue->rear = -1;
    for (int i = 0; i < MAX; i++) {
        queue->array[i] = 0; 
    }
}

int isfull(struct que *queue){
    return ((queue->rear + 1) % MAX == queue->front); 
}

int isempty(struct que *queue){
    return (queue->front == -1); 
}
