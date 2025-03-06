#include "queue.h"

int enqueue(struct que *queue, long n){
    if((queue->rear+1)%MAX==queue->front){
        exit(1);
        return 1;
    }
    
    if(queue->front==-1||queue->rear==-1){
        queue->front=0;
    }

    queue->rear=(queue->rear+1)%MAX;
    queue->array[queue->rear]=n;
    return 0;
}

long dequeue(struct que *queue){
    long n;
    if(queue->front==-1&&queue->rear==-1){
        exit(1);
        return 1;
    }
    if(queue->front==queue->rear){
        n=queue->array[queue->front];
        queue->front=-1;
        queue->rear=-1;
        return n;
    }
    n=queue->array[queue->front];
    queue->front=(queue->front+1)%MAX;
    return n;
}

void innitQueue(struct que * queue){
    queue->front=-1;
    queue->rear=-1;
    for(int i=0;i<MAX;i++){
        queue->array[i]=(long)NULL;
    }
}

int isfull(struct que * queue){
    if((queue->rear+1)%MAX==queue->front){
        return 1;
    }
    return 0;
}

int isempty(struct que * queue){
    if(queue->front==-1&&queue->rear==-1){
        return 1;
    }
    return 0;
}