#ifndef _MAIN_H
#define _MAIN_H

#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"
#include "unistd.h"
#include "sys/stat.h"
#include "math.h"
#include "string.h"
#include "linux/limits.h"

#define MAX_IDs 100000
#define COUNT_PRINT_ROWS 10
#define NODE_TYPE StatData

typedef struct StatData {
    long id;
    int count;
    float cost;
    unsigned int primary:1;
    unsigned int mode:3;
} StatData;

typedef struct StatBuffer {
    StatData *ptr;
    long size;
} StatBuffer;

#include "hash.h"

#endif