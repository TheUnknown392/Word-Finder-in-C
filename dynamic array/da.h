// #define  DA_MIN_ 10
// DA_OUTOFBOUND to enable out of bound message
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

 struct DA{
    char *start;
    size_t capacity;
    size_t size;
};

void da_innit(struct DA *,size_t);
char da_access(struct DA *,size_t);
bool da_append(struct DA *, char);
bool da_insert(struct DA *, size_t, char);
void outOfBound(char *);