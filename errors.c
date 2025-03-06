#include "errors.h"

void error(enum type form,...){
    va_list args;
    va_start(args,form);
    switch (form){
    case FORMAT:
        printf("The argument format is incorrect. please cheak and try again");
        exit(form);
        break;
    case NOFILE:
        printf("File could not be opened");
        exit(form);
    default:
        vprintf("%s",args);
        exit(NONE);
        break;
    }
    va_end(args);
}
