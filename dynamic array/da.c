#include "da.h"
// this is made for learning purposes only.



// initializes your DA with initial space
void da_innit(struct DA * da, size_t size){
    da->capacity=size;
    da->size=0;
    da->start=(char *)malloc(size * sizeof(char));
}

// peeking an index of da, returns '\0' if outofbounds returns data
char da_access(struct DA * da,size_t no){
    if(no>da->size){
#ifdef DA_OUTOFBOUND
        outOfBound("da_access");
        return  '\0';
#else
        return  '\0';
#endif
    }
    return da->start[no];
}

// appends a character at the end of array returns bool
bool da_append(struct DA * da, char ch){
    if(da->size==da->capacity){
        char * temp = da->start;
        da->start=(char *)realloc(da->start,da->capacity+sizeof(char));
        da->capacity=da->capacity+sizeof(char);
        if(da->start==NULL) return false;
        if(temp!=da->start){
            free(temp);
        }
    }else if(da->size>da->capacity){
#ifdef DA_OUTOFBOUND
        outOfBound("da_append");
        return  false;
#else
        return  false;
#endif
    }
    da->start[da->size]=ch;
    da->size++;
    return true;
}

// inserting data at specific location within (available space + 1) returns boolean
bool da_insert(struct DA * da, size_t pos, char ch){
    if(pos>da->capacity) {
#ifdef DA_OUTOFBOUND
        outOfBound("da_insert");
        return  false;
#else
        return  false;
#endif
    }
    if(pos==da->capacity){
        return da_append(da,ch);
    }else{
        da->start[pos]=ch;
        return true;
    }
}

// prints where out of bound occured in DA
void outOfBound(char *ch){
    printf("/n-----------------------------------/n");
    printf("out of bounds: %s",ch);
    printf("/n-----------------------------------/n");
}