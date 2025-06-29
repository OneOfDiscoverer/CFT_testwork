#include "hash.h"

HashTable *create_hashtable(int size) {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->size = size;
    ht->count = 0;
    ht->buckets = calloc(size, sizeof(HashNode *));
    return ht;
}

void insert(HashTable *ht, int key, NODE_TYPE value) { 
    HashNode *new_node = malloc(sizeof(HashNode));
    new_node->key = key;
    new_node->value = value;
    ht->buckets[key] = new_node;
    ht->count++;
}

int get(HashTable *ht, int key, NODE_TYPE **value) {
    HashNode *node = ht->buckets[key];
    if (node && node->key == key) {
        *value = &node->value;
        return 1;
    }
    return 0;
}

void delete(HashTable *ht, int key) {
    HashNode *node = ht->buckets[key];
    if (node && node->key == key) {
        free(node);
        ht->buckets[key] = 0;
        ht->count--;
        return;
    }
}

void free_hashtable(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        HashNode *node = ht->buckets[i];
            free(node);
    }
    free(ht->buckets);
    free(ht);
}

void print_hashtable(HashTable *ht) {
    printf("[size: %d, rows: %d]:\n", ht->size, ht->count);
    for (int i = 0; i < ht->size; i++) {
        HashNode *node = ht->buckets[i];
        if (node) {
            printf("[%03d]: ", i);
            printf("{%d: %d}", node->key, node->value.id);
            printf("\n");
        }
    }
}