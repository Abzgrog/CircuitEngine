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
            if(key == '\n') {
                char* command = global_program->command_console->current_user_command.buffer;
                log_message(global_loger, DEBUG, command);

                int msg_count = get_msg_count(global_program->command_console);

                char* msg_count_str[MAX_LOG_MESSAGES];
                sprintf(msg_count_str, "%d", msg_count);
                log_message(global_loger, DEBUG, msg_count_str);

                console_add_message(global_program->command_console, command, FALSE);
                command_proccess(command, global_program->command_console);
                clear_user_input_buffer(global_program->command_console);
            } else {
            int count = 0;
            char new_char = (char)key;
            count = global_program->command_console->current_user_command.counter;
            
            if(count >= MAX_COMMAND_LENGTH) {
                console_add_message(global_program->command_console, "Unknown command", FALSE);
                clear_user_input_buffer(global_program->command_console);
                return;
            }
            global_program->command_console->current_user_command.counter++;

            global_program->command_console->current_user_command.buffer[count] = new_char;
            global_program->command_console->current_user_command.buffer[count + 1] = '\0';
            //console_delete_message(global_program->command_console, 0, TRUE);
            
            log_message(global_loger, DEBUG, global_program->command_console->current_user_command.buffer);
            console_add_message(global_program->command_console, global_program->command_console->current_user_command.buffer, TRUE);
            }
        }
    }
    else {
        log_message(global_loger, WARNING, ":101");
    }
    
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