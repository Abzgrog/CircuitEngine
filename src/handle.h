#ifndef HANDLE_H
#define HANDLE_H
struct MEVENT;
#include "ui.h"


void mouse_handle(MEVENT mv);
void keyboard_handle(int key);
void menu_navigation(MenuButtons* mb, Direction dir);
Direction get_direction(int key);
void program_state_menu_handle();
void program_state_circuit_handle();
void program_state_settings_handle();
void program_state_logger_handle();


#endif //HANDLE_H