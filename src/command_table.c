// command_table.c
#include "command_table.h"
#include <stdlib.h>
#include <string.h>

static unsigned int hash(const char* key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % 101;
}

CommandTable* create_command_table() {
    CommandTable* table = malloc(sizeof(CommandTable));
    for (int i = 0; i < 101; i++)
        table->buckets[i] = NULL;
    return table;
}

void free_command_table(CommandTable* table) {
    for (int i = 0; i < 101; i++) {
        CommandNode* node = table->buckets[i];
        while(node) {
            CommandNode* tmp = node;
            node = node->next;
            free(tmp->key);
            free(tmp);
        }
    }
    free(table);
}

bool insert_command(CommandTable* table, const char* key, CommandFunc func) {
    unsigned int index = hash(key);
    CommandNode* node = table->buckets[index];
    while(node) {
        if(strcmp(node->key, key) == 0) {
            node->func = func; 
            return true;
        }
        node = node->next;
    }

    CommandNode* new_node = malloc(sizeof(CommandNode));
    if (!new_node) return false;

    new_node->key = malloc(strlen(key) + 1);
    if (!new_node->key) {
        free(new_node);
        return false;
    }
    strcpy(new_node->key, key);

    new_node->func = func;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    return true;
}

CommandFunc get_command(CommandTable* table, const char* key) {
    unsigned int index = hash(key);
    CommandNode* node = table->buckets[index];
    while(node) {
        if(strcmp(node->key, key) == 0)
            return node->func;
        node = node->next;
    }
    return NULL;
}

bool remove_command(CommandTable* table, const char* key) {
    unsigned int index = hash(key);
    CommandNode* node = table->buckets[index];
    CommandNode* prev = NULL;
    while(node) {
        if(strcmp(node->key, key) == 0) {
            if(prev) prev->next = node->next;
            else table->buckets[index] = node->next;
            free(node->key);
            free(node);
            return true;
        }
        prev = node;
        node = node->next;
    }
    return false;
}
