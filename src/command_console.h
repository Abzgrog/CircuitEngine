#ifndef COMMAND_CONSOLE_H
#define COMMAND_CONSOLE_H

#define MAX_COMMAND_LENGTH 20
#define MAX_LOG_MESSAGES 500
#define MAX_LOG_MESSAGES_LENGTH 250

#include "command_table.h"
#include "logger.h"
#include <ncurses.h>
#include <panel.h>

typedef struct UserInputCommand {
    char buffer[MAX_COMMAND_LENGTH];
    int counter;
} UserInputCommand;

typedef struct ValidatedCommand {
    char* main_command;
} ValidatedCommand;

typedef struct CommandConsole {
    UserInputCommand current_user_command;
    CommandTable* func_table; 
    char buffer[MAX_LOG_MESSAGES][MAX_LOG_MESSAGES_LENGTH];
    int current_log_messages_count;
    WINDOW* win;
    PANEL* pan;
} CommandConsole;

void clear_user_input_buffer(CommandConsole* cli);
void console_add_message(CommandConsole* cli, const char* msg, bool current_user_input);
void draw_command_console_buffer(CommandConsole* cli, bool current_user_input);
void draw_user_input_buffer(CommandConsole* cli);
void command_proccess(char* non_validated_command, CommandConsole* cli);
void init_func_table_functions(CommandConsole* cli);
int get_msg_count(CommandConsole* cli);
void console_delete_message(CommandConsole* cli, int index, bool delete_last);
void cli_command_clear();

ValidatedCommand* validate_command(char* user_input);
CommandConsole* init_command_console();


#endif //COMMAND_CONSOLE_H