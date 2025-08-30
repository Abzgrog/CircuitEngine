// command_table.h
#ifndef COMMAND_TABLE_H
#define COMMAND_TABLE_H

#include <stdbool.h>

typedef void (*CommandFunc)(void);

typedef struct CommandNode {
    char* key;
    CommandFunc func;
    struct CommandNode* next;
} CommandNode;

typedef struct CommandTable {
    CommandNode* buckets[101]; 
} CommandTable;

CommandTable* create_command_table();
void free_command_table(CommandTable* table);
bool insert_command(CommandTable* table, const char* key, CommandFunc func);
CommandFunc get_command(CommandTable* table, const char* key);
bool remove_command(CommandTable* table, const char* key);

#endif
