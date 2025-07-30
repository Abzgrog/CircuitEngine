#include <ncurses.h>
#include "utils.h"
#include "logger.h"
#include "program.h"
#include "globals.h"
#include "handle.h"
#include "ui.h"
#define KEY_ESC 27

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
    if(key == KEY_UP || key == KEY_DOWN) {
        Direction dir = get_direction(key);
        MenuButtons* mb = get_menu_buttons();
        menu_navigation(mb, dir);
    } else {
        //todo "enter, f2"
    }
}

void program_state_circuit_handle(); //todo circuithandle
void program_state_settings_handle();// todo settingshandle
void program_state_logger_handle(); //todo loggerhandle

void keyboard_handle(int key) {
    if(global_program->program_state == ProgramStateMenu) {
        program_state_menu_handle(key);
    } //todo else variations
    
    /*switch (key)
    {
        case KEY_F(2):
        //todo logger window
        break;
    case KEY_ENTER: 
        //todo add 3 state settings circuit menu
        break;
    case KEY_ESC:
        log_message(global_logger, DEBUG, "Esc was pressed");
        global_program->program_state = ProgramStateExiting; 
    break;
    case KEY_UP:
        MenuButtons* mb = get_menu_buttons();
        menu_navigation(mb, UP);
        break;
    case KEY_DOWN:
        MenuButtons* mb = get_menu_buttons();
        menu_navigation(mb, UP);
        break;
    case KEY_LEFT:
        MenuButtons* mb = get_menu_buttons();
        menu_navigation(mb, UP);
        break;
    case KEY_RIGHT:
        MenuButtons* mb = get_menu_buttons();
        menu_navigation(mb, UP);
        break;
    case ERR:
        break;
    default:
        log_message(global_logger, WARNING, "Unknown key in handler");
    
        break;
        
    }
        */
}