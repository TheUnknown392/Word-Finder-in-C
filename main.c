#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1024

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
size_t searchStrLen(int args, char * arg[]);

int main(const int args, const char* argv[]){
    if (args==1)
    {
        printf("Wrong format. Please try again.");
        exit(1); 
    }
    FILE * fp = fopen(argv[1],"r+");
    if(fp==NULL){
        printf("Couldn't open file");
        fclose(fp);
        exit(1);
    }

    struct que queue;
    innitQueue(&queue);
    char *word=(char *)malloc(sizeof(char)*256);
    for(size_t i=2;i<args;i++){
        while(fscanf(fp," %s ",word)!=EOF){
            if(strcmp(argv[i],word)==0){
                enqueue(&queue,ftell(fp)-strlen(word));
            }
        }
    }

    char ch;
    while(!isempty(&queue)){
        fseek(fp,dequeue(&queue),SEEK_SET);
        while((ch=fgetc(fp))!='\n'&&ch!=EOF){
            printf("%c",ch);
        }
        printf("\n");
    }


    fclose(fp);
    free(word);
    
    return 0;
}

size_t searchStrLen(int args, char * arg[]){
    size_t num=0;
    for (size_t i = 2;i<args; i++)
    {
        num=num+strlen(arg[i]);
    }
    return num;
}

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