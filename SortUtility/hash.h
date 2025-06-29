#ifndef _HASH_H
#define _HASH_H

#include "stdio.h"
#include "stdlib.h"
#include "main.h"

#ifndef NODE_TYPE
#error "NODE_TYPE must be defined before including hash.h"
#endif

typedef struct HashNode {
    int key;
    NODE_TYPE value;
} HashNode;

typedef struct {
    HashNode **buckets;
    int size;
    int count;
} HashTable;

HashTable *create_hashtable(int size);
void insert(HashTable *ht, int key, NODE_TYPE value);
int get(HashTable *ht, int key, NODE_TYPE **value);
void delete(HashTable *ht, int key);
void free_hashtable(HashTable *ht);
void print_hashtable(HashTable *ht);

#endif