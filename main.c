#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "queue.h"

size_t searchStrLen(int args, const char * arg[]);

int main(const int args, const char* argv[]){
    if (args==1){
        printf("Wrong format. Please try again.");
        exit(1); 
    }
    FILE * fp = fopen(argv[1],"r+");
    if(fp==NULL){
        printf("Couldn't open file");
        fclose(fp);
        exit(1);
    }

    struct que queue; // Stores end of maching character
    // struct que queueStart; // Stores start of the line where maching character is found
    innitQueue(&queue);
    // innitQueue(&queueStart);
    
    char *word=(char *)malloc(sizeof(char)*searchStrLen(args,argv));
    for(int i=2;i<args;i++){
        while(fscanf(fp," %s",word)!=EOF){
            if(strcmp(argv[i],word)==0){
                enqueue(&queue,ftell(fp));
            }
        }
    }
    //asd
    //xxx.xxxxxxx.xxxxxxx\n asd sadfasdf asdfds asds asdfasdf asdf
    char ch;
    // fseek(fp,0,SEEK_END);
    // const long endCur=ftell(fp);
    while(!isempty(&queue)){ // until the whole queue is empty
        fseek(fp,dequeue(&queue),SEEK_SET);
        while((ch=fgetc(fp))!='\n'){ // moves cursur backward until it encounters new line
            if((ftell(fp)<=1)){
                rewind(fp);
                ch=fgetc(fp);
                break;
            }else{
                fseek(fp,-2,SEEK_CUR);
                ch=fgetc(fp);
            }
        }
        do{
            printf("%c",ch);
            ch=fgetc(fp);
        }while(ch!='\n'&&ch!=EOF);
        // if(!(ftell(fp)+1>=endCur)){
        //     enqueue(&queueStart,ftell(fp)+1);
        // }else if(ftell(fp)==0){
        //     enqueue(&queueStart,ftell(fp));
        // }else{
        // }
        // enqueue(&queueStart,ftell(fp));
    }
    // while(!isempty(&queueStart)){ // prints the character until while line is printed
    //     fseek(fp,dequeue(&queueStart),SEEK_SET);
    //     do{
    //         printf("%c",ch);
    //         ch=fgetc(fp);
    //     }while(ch!='\n'&&ch!=EOF);
    //     printf("\n");
    // }

    fclose(fp);
    free(word);
    
    return 0;
}

size_t searchStrLen(int args, const char * arg[]){
    size_t num=0;
    for (int i = 2;i<args; i++)
    {
        num=num+strlen(arg[i]);
    }
    return num;
}