#include <ncurses.h>
#include <string.h>
#include "command_console.h"
#include "utils.h"
#include "logger.h"
#include "program.h"
#include "globals.h"
#include "handle.h"
#include "ui.h"
#define KEY_ESC 27
bool skip_first_enter = 0;


void mouse_handle(MEVENT mv) {
    return;
}

Direction get_direction(int key) {
    if(key == KEY_UP) {
        return UP;
    } else if(key == KEY_DOWN) {
        return DOWN;
    } else {
        return NONE_DIRECTION;
    }
}



void menu_navigation(MenuButtons* mb, Direction dir) {
    static int selected = 0;
    
    for(int i = 0; i < MENU_BUTTONS_COUNT; i++) {
        if(mb->buttons[i]->selected) {
            mb->buttons[i]->selected = false;
            clear_button_extra(mb->buttons[i]);
            if(dir == UP) {
                if(i == 0) {
                    mb->buttons[MENU_BUTTONS_COUNT - 1]->selected = true;
                    return;
                }
                mb->buttons[i - 1]->selected = true;
                return;
            } else if(dir == DOWN){
                if(i == MENU_BUTTONS_COUNT - 1) {
                    mb->buttons[0]->selected = true;
                    return;
                }
                mb->buttons[i + 1]->selected = true;
                return;
            }
        }
    }
}
void program_state_menu_handle(int key) {
    MenuButtons* mb = get_menu_buttons();
    if(key == KEY_UP || key == KEY_DOWN) {
        Direction dir = get_direction(key);
        menu_navigation(mb, dir);
    }

    if(key == KEY_ESC) {
        global_program->program_state = ProgramStateExiting;
    }

    if(key == KEY_F(2)) {
        global_program->program_state = ProgramStateLogger;
    }

    if(key == '\n') {
        int idx = 0;
        for(int i = 0; i < MENU_BUTTONS_COUNT; i++) {
            if(mb->buttons[i]->selected) {
                idx = i;
            }
        }
        if(strcmp(mb->buttons[idx]->name, "EXIT") == 0) {
            global_program->program_state = ProgramStateExiting;
        } 
        
        if(strcmp(mb->buttons[idx]->name, "NEW CIRCUIT") == 0) {
            global_program->program_state = ProgramStateCircuitProccess;
            global_program->current_window = CommandWindow;
            skip_first_enter = TRUE;
            return;
        } 

        if(strcmp(mb->buttons[idx]->name, "LOAD CIRCUIT") == 0) {
        } 

        if(strcmp(mb->buttons[idx]->name, "SETTINGS") == 0) {
        } 
    }
}

void program_state_circuit_handle(int key) {
    if(global_program->program_state == ProgramStateCircuitProccess) {
        if(key == KEY_ESC) {
            global_program->program_state = ProgramStateMenu;
            global_program->current_window = MainWindow;
            clear();
            refresh();
        }
        
        if(global_program->current_window == CommandWindow && global_program->program_state == ProgramStateCircuitProccess) {
            handle_console_input(key);
        }
    }
    else {
        log_message(global_loger, WARNING, ":101");
    }
    
}
void handle_console_input(int key) {
    CommandConsole* cli = global_program->command_console;
    UserInputCommand* user_command = &cli->current_user_command;

    if (key == '\n') { // Enter
        if (user_command->counter > 0) {
            char command_to_process[MAX_COMMAND_LENGTH];
            strncpy(command_to_process, user_command->buffer, user_command->counter);
            command_to_process[user_command->counter] = '\0';

            console_add_message(cli, command_to_process); // Добавить команду в историю
            command_proccess(command_to_process, cli); // Передать команду на обработку
            clear_user_input_buffer(cli); // Очистить текущую строку ввода
            draw_command_console_buffer(global_program->command_console);
        }
    } else if (key == KEY_BACKSPACE || key == 127) { // Backspace
        if (user_command->counter > 0) {
            user_command->counter--;
            user_command->buffer[user_command->counter] = '\0';
        }
    } else if (key >= 32 && key <= 126) { // Обычные печатаемые символы
        if (user_command->counter < MAX_COMMAND_LENGTH - 1) {
            user_command->buffer[user_command->counter] = (char)key;
            user_command->counter++;
            user_command->buffer[user_command->counter] = '\0';
        }
    }
    draw_command_console_buffer(cli); // Обновить буфер консоли
    draw_user_input_buffer(cli); // Обновить строку ввода
}

void program_state_settings_handle();// todo settingshandle
void program_state_logger_handle(); //todo loggerhandle

void keyboard_handle(int key) {
    if(global_program->program_state == ProgramStateMenu) {
        program_state_menu_handle(key);
    } 
    if(global_program->program_state == ProgramStateCircuitProccess) {
        if(skip_first_enter && key == '\n') {
            skip_first_enter = false;
            return;
        }
        program_state_circuit_handle(key);
    }
    //todo else variations
    
}