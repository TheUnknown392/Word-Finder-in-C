#ifndef __ERROR_IMPLEMENTATION
#define __ERROR_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


enum type{
    FORMAT = 1,
    NOFILE,
    NOTIMPLEMENTED,
    NONE
};

void error(enum type form,...);
#endif