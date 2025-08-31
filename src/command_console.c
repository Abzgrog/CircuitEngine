#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include <stdlib.h>
#include "program.h"
#include "command_console.h"
#include "globals.h"
#include "logger.h"
#include "command_table.h"
#include "components.h"


#define HELP_STR_INTRO "Current avalible commands:"
#define HELP_STR_COMMAND_EXIT "Exit:    Leave from current circuit"
#define HELP_STR_COMMAND_LIST "Ls:      Give list all components of circuit"
#define HELP_STR_COMMAND_CLEAR"Cls:     Clearing console visible buffer"
#define HELP_STR_COMMAND_SAVE "Sv:      Saving circuit to current openned file"
#define HELP_STR_COMMAND_SAVE_AND_EXIT "Svex:    Saving circuit to current openned file than exit to menu"
#define HELP_STR_COMMAND_CREATE_COMPONENT "Cp:      Creating component(Cp(CpType, val1, val2, coordX, coordY))"

#define RED 1
#define GREEN 2
#define CYAN 3
#define WHITE 4

#define CONSOLE_HEIGHT 25
#define CONSOLE_WIDTH  70

CommandConsole* init_command_console() {
    static CommandConsole cli_instance;
    static bool initialized = false;

    if (!initialized) {
        cli_instance.win = newwin(CONSOLE_HEIGHT, CONSOLE_WIDTH, 4, 110);
        cli_instance.pan = new_panel(cli_instance.win);
        nodelay(cli_instance.win, TRUE); 
        keypad(cli_instance.win, TRUE);  

        for (int i = 0; i < MAX_LOG_MESSAGES; i++) {
            cli_instance.buffer[i][0] = '\0';
        }

        cli_instance.current_user_command.buffer[0] = '\0';
        cli_instance.current_user_command.counter = 0;

        cli_instance.func_table = create_command_table();
        
        init_func_table_functions(&cli_instance);
        initialized = true;
    }

    box(cli_instance.win, 0, 0);
    wrefresh(cli_instance.win);
    update_panels();
    doupdate();

    console_add_message(&cli_instance, "Console inited!");

    return &cli_instance;
}

void cli_command_clear() {
    console_clear(global_program->command_console); 
    log_message(global_loger, DEBUG, "cli_clear()");
}

void cli_command_help() {
    console_clear(global_program->command_console);
    console_add_message(global_program->command_console, HELP_STR_INTRO);
    console_add_message(global_program->command_console, HELP_STR_COMMAND_CLEAR);
    console_add_message(global_program->command_console, HELP_STR_COMMAND_EXIT);
    console_add_message(global_program->command_console, HELP_STR_COMMAND_LIST);
    console_add_message(global_program->command_console, HELP_STR_COMMAND_SAVE);
    console_add_message(global_program->command_console, HELP_STR_COMMAND_SAVE_AND_EXIT);
    console_add_message(global_program->command_console, HELP_STR_COMMAND_CREATE_COMPONENT);
}

void cli_command_list() {
    //todo
}

void cli_command_save() {
    //todo
}

void cli_command_save_and_exit() {
    //todo
}

void cli_command_create_component(ComponentType, int val1, bool val2, int coord1, int coord2) {
    //todo
}

void cli_command_exit() {
    global_program->current_window = MainWindow;
    global_program->program_state = ProgramStateMenu;
}
void init_func_table_functions(CommandConsole* cli) {
    CommandTable* ct = cli->func_table;

    insert_command(ct, "Cls", cli_command_clear);
    insert_command(ct, "Exit", cli_command_exit);
    insert_command(ct, "Ls", cli_command_list);
    insert_command(ct, "Help", cli_command_help);
}

void console_add_message(CommandConsole* cli, const char* msg) {
    if (!cli) return;

    for (int i = 1; i < MAX_LOG_MESSAGES; i++) {
        strcpy(cli->buffer[i-1], cli->buffer[i]);
    }

    strncpy(cli->buffer[MAX_LOG_MESSAGES-1], msg, MAX_LOG_MESSAGES_LENGTH-1);
    cli->buffer[MAX_LOG_MESSAGES-1][MAX_LOG_MESSAGES_LENGTH-1] = '\0';

    draw_command_console_buffer(cli);
    draw_user_input_buffer(cli); 
}

void console_delete_message(CommandConsole* cli, int index) {
    int count = get_msg_count(cli);
    if(count < 1) {
        return;
    }
    cli->buffer[count - 1][0] = '\0';
}

void draw_command_console_buffer(CommandConsole* cli) {
    if (!cli || !cli->win) return;

    werase(cli->win);
    box(cli->win, 0, 0);

    int max_y = CONSOLE_HEIGHT - 2; // минус рамка
    int start_line = 0;

    if (MAX_LOG_MESSAGES > max_y) {
        start_line = MAX_LOG_MESSAGES - max_y;
    }

    int line = 1;
    for (int i = start_line; i < MAX_LOG_MESSAGES && line < CONSOLE_HEIGHT - 1; i++) {
        if (cli->buffer[i][0] != '\0') {
            mvwprintw(cli->win, line, 1, "%s", cli->buffer[i]);
                line++;
        }
    }

    wrefresh(cli->win);
    update_panels();
    doupdate();
}

void console_clear(CommandConsole* cli) {
    if (!cli) return;

    for (int i = 0; i < MAX_LOG_MESSAGES; i++) {
        cli->buffer[i][0] = '\0';
    }
    draw_command_console_buffer(cli);
}

int get_msg_count(CommandConsole* cli) {
    int count = 0;
    
    for(int i = 0; i < MAX_LOG_MESSAGES; i++) {
        if(cli->buffer[i][0] != '\0') {
            count++;
        }
    }

    return count;
}

void clear_user_input_buffer(CommandConsole* cli) {
    cli->current_user_command.buffer[0] = '\0';
    cli->current_user_command.counter = 0;
}

void draw_user_input_buffer(CommandConsole* cli) {
    if (!cli || !cli->win) return;

    int input_line = CONSOLE_HEIGHT - 2; // last line
    mvwprintw(cli->win, input_line, 1, "%*s", CONSOLE_WIDTH - 2, ""); 
    mvwprintw(cli->win, input_line, 1, "> %s", cli->current_user_command.buffer);
    wrefresh(cli->win);
    update_panels();
    doupdate();
}

ValidatedCommand* validate_command(char* user_input) {
    ValidatedCommand* command = malloc(sizeof(ValidatedCommand));
    if (!command) return NULL; 
    command->main_command = user_input;
    //todo arguments in commands
    return command;
}
void command_proccess(char* non_validated_command, CommandConsole* cli) {
    ValidatedCommand* val_command = validate_command(non_validated_command);
    
    log_message(global_loger, INFO, val_command->main_command);

    if (!val_command) {
        console_add_message(cli, "Memory allocation error");
        return;
    }

    CommandFunc f = get_command(cli->func_table, val_command->main_command);
    if (f) {
        f();
    } else {
        char msg[100];
        snprintf(msg, sizeof(msg), "Unknown command: %s", val_command->main_command);
        console_add_message(cli, msg);
        console_add_message(cli, "Type \"Help\" for more list of commands!");
    }

    free(val_command); 
}