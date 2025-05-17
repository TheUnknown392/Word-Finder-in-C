/*
    KNOWN BUGS/annoyance:
            2: (fixed) when there is duplication when printing out the line if there are multiple search words present
            3: (fixed) don't like how I have to free.
            4: still don't like how it searches for same words
	    5: I cannot search for a word that contains any character defined in ESCAPE. eg: i can't find for [info] but i can for info in test log files.
            
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue//queue.h"

#define BUFF 1024
#define ESCAPE " \r\n,.[]{}():;'"
void printQueue(struct que *queue,struct que * savedLine, FILE * fp);
int stringCompair(const char *ch,const char *str);

int main(const int args, const char* argv[]){

    if(args<3){
        printf("Incorrect argument\n./main <file> <argument(s)>\n\tEG: ./main ./yo/hi.txt test 1\n");
        exit(1);
    }

    struct que queue; 
    innitQueue(&queue);

    struct que saveLine;
    innitQueue(&saveLine);

    FILE * fp = fopen(argv[1],"rb");
    if(fp==NULL){
        printf("Couldn't open file or argument incorrect. ./main <file> <argument(s)>\n\tEG: ./main ./yo/hi.txt test 1");
        exit(1);
    }

    
    char *line=(char *)malloc(sizeof(char)*BUFF);
    char *temp;
    
    size_t lineNo=0;
    while(fgets(line,BUFF,fp)!=NULL){ // takes the whole line
        ++lineNo;
        int inserted = 0;
        temp=strtok(line,ESCAPE);
        while(temp!=NULL){ // takes a word from a the line
            for(int i=2;i<args;i++){
                if(stringCompair(argv[i],temp)){
                    if(isfull(&queue)){
                        printQueue(&queue,&saveLine,fp);
                    }
                    enqueue(&queue,ftell(fp)-2); // fgets scans until the cursor points to first character of another line so we go back 2 to go back to first line. if it was -1, cursor would point to new line.
                    enqueue(&saveLine,lineNo);
                    inserted = 1;
                    break;
                }
            }
            if(inserted) break;            
            temp=strtok(NULL,ESCAPE); // ignores the carriage return and new line when strtok gets those too by reading the string before new line.
        }
    }

    printQueue(&queue,&saveLine,fp);
    fclose(fp);
    free(line);
    return 0;
}

void printQueue(struct que *queue,struct que *savedLine, FILE * fp){
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
        printf("%zu:\t%s",dequeue(savedLine),line);
    }
    free(line);
}

int stringCompair(const char *arg,const char *cmp){
    int i=0;
    while((arg[i]!=(char)'\0')&&(cmp[i]!=(char)'\0')){
        if(!(tolower(arg[i])==tolower(cmp[i]))){
            return 0;
        }
        i++;
    }
    return 1;
}
