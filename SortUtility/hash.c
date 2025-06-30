#include "hash.h"

HashTable *create_table(int size) {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->size = size;
    ht->count = 0;
    ht->buckets = calloc(size, sizeof(NODE_TYPE *));
    return ht;
}

void insert(HashTable *ht, int key, NODE_TYPE value) { 
    NODE_TYPE *new_node = malloc(sizeof(NODE_TYPE));
    *new_node = value;
    ht->buckets[key] = new_node;
    ht->count++;
}

int get(HashTable *ht, int key, NODE_TYPE **value) {
    NODE_TYPE *node = ht->buckets[key];
    if (node) {
        *value = node;
        return 1;
    }
    return 0;
}

void delete(HashTable *ht, int key) {
    NODE_TYPE *node = ht->buckets[key];
    if (node) {
        free(node);
        ht->buckets[key] = 0;
        ht->count--;
        return;
    }
}

void free_table(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        NODE_TYPE *node = ht->buckets[i];
            free(node);
    }
    free(ht->buckets);
    free(ht);
}

void print_table(HashTable *ht) {
    printf("[size: %d, rows: %d]:\n", ht->size, ht->count);
    for (int i = 0; i < ht->size; i++) {
        NODE_TYPE *node = ht->buckets[i];
        if (node) {
            printf("[%03d]: ", i);
            printf("{%d}", node->id);
            printf("\n");
        }
    }
}