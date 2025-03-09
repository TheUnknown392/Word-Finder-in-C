/*
    KNOWN BUGS:
            1: it can't find if there is a line smaller than 2 character
            2: when there is duplication when printing out the line if there are multiple search words present
            
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "queue.h"

#define BUFF 1024
void printQueue(struct que *queue, FILE * fp);

int main(const int args, const char* argv[]){

    struct que queue; 
    innitQueue(&queue);

    FILE * fp = fopen(argv[1],"rb");
    if(fp==NULL){
        printf("Couldn't open file or argument incorrect. ./main <file> <argument(s)>\n\tEG: ./main ./yo/hi.txt test 1");
        fclose(fp);
        exit(1);
    }

    char *line=(char *)malloc(sizeof(char)*BUFF);
    char *temp;
    
    for(int i=2;i<args;i++){
        while(fgets(line,BUFF,fp)!=NULL){ // takes the whole line
        temp=strtok(line," ");
            while(temp!=NULL){ // takes a word from a the line
                if(strcmp(argv[i],temp)==0){
                    if(isfull(&queue)){
                        printQueue(&queue,fp);
                    }
                    enqueue(&queue,ftell(fp)-2); // fgets scans until the cursor points to first character of another line so we go back 2 to go back to first line. if it was -1, cursor would point to new line.
                    // BUG 1
                    break;
                }
                temp=strtok(NULL," ");
            }
        }
        rewind(fp);
    }
    printQueue(&queue,fp);
    fclose(fp);
    free(line);
    return 0;
}

void printQueue(struct que *queue, FILE * fp){
    char *line=(char *)malloc(sizeof(char)*BUFF);
    char ch;
    while(!isempty(queue)){
        fseek(fp,dequeue(queue),SEEK_SET);
        while((ch=fgetc(fp))!='\n'){ // moves cursur backward until it encounters new line
            if((ftell(fp)<=1)){
                rewind(fp);
                break;
            }else{
                fseek(fp,-2,SEEK_CUR);
            }
        }
        fgets(line,BUFF,fp);
        printf("%s\n",line);
    }
    free(line);
}