/*
    KNOWN BUGS/annoyance:
            2: (fixed) when there is duplication when printing out the line if there are multiple search words present
            3: don't like how I have to free.
            
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "queue//queue.h"

#define BUFF 1024
#define ESCAPE " \r\n,.[]{}():;'"
void printQueue(struct que *queue,struct que *lineNumbers, FILE * fp);
char * stringLower(const char *str);

int main(const int args, const char* argv[]){

    if(args<3){
        printf("Incorrect argument\n./main <file> <argument(s)>\n\tEG: ./main ./yo/hi.txt test 1\n");
        exit(1);
    }

    struct que queue; 
    innitQueue(&queue);

    struct que lineNumbers; 
    innitQueue(&lineNumbers);

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
                char *freeA=stringLower(argv[i]);
                char *freeB=stringLower(temp);
                if(strcmp(freeA,freeB)==0){
                    free(freeA);
                    free(freeB);
                    if(isfull(&queue)){
                        printQueue(&queue,&lineNumbers,fp);
                    }
                    enqueue(&queue,ftell(fp)-2); // fgets scans until the cursor points to first character of another line so we go back 2 to go back to first line. if it was -1, cursor would point to new line.
                    enqueue(&lineNumbers,lineNo);
                    inserted = 1;
                    break;
                }
                free(freeA);
                free(freeB);
            }
            if(inserted){
                break;            
            }
            temp=strtok(NULL,ESCAPE); // ignores the carriage return and new line when strtok gets those too by reading the string before new line.
        }
    }
    
    printQueue(&queue,&lineNumbers,fp);
    fclose(fp);
    free(line);
    return 0;
}

void printQueue(struct que *queue,struct que * lineNumbers, FILE * fp){
    char *line=(char *)malloc(sizeof(char)*BUFF);
    char ch;
    long save = ftell(fp);
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
        printf("%zu:\t%s",dequeue(lineNumbers),line);
    }
    fseek(fp,save,SEEK_SET);
    free(line);
}

char * stringLower(const char *ch){
    int i=0;
    char *str=(char *)malloc(strlen(ch)+1);
    if(str==NULL) exit(1);
    strcpy(str,ch);
    while(str[i]!=(char)'\0'){
        for(size_t j=0;j<(sizeof(ESCAPE)/sizeof(ESCAPE[0]))-1;j++){
            if(str[i]!=ESCAPE[j]){
                str[i]=tolower(str[i]);
            }else{
                // shift left and over write anything defined in ESCAPE
                int k=i;
                while(str[k]!='\0'){
                    str[k]=str[k+1];
                    k++;
                }
                str[k]='\0';
            }
        }
        i++;
    }
    str[i]='\0';
    return str;
}