#ifndef _HASH_H
#define _HASH_H

#include "stdio.h"
#include "stdlib.h"
#include "main.h"

#ifndef NODE_TYPE
#error "NODE_TYPE must be defined before including hash.h"
#endif

typedef struct {
    NODE_TYPE **buckets;
    int size;
    int count;
} HashTable;

HashTable *create_table(int size);
void insert(HashTable *ht, int key, NODE_TYPE value);
int get(HashTable *ht, int key, NODE_TYPE **value);
void delete(HashTable *ht, int key);
void free_table(HashTable *ht);
void print_table(HashTable *ht);

#endif