#ifndef UI_H
#define UI_H

#include "components.h"

#define MENU_BUTTONS_COUNT 4
#define BUFFER_WIDTH 50
#define BUFFER_HEIGHT 30

typedef struct Screen {
    char buffer[BUFFER_HEIGHT][BUFFER_WIDTH];
} Screen;

typedef struct Button {
    int x;
    int y;
    char* name;
    bool selected;
} Button;

typedef struct MenuButtons {
    Button* buttons[MENU_BUTTONS_COUNT];
} MenuButtons;
MenuButtons* get_menu_buttons();
void draw_button_extra(Button* b);
void clear_button_extra(Button* b);
void draw_component();
void draw_all_components();
void draw_menu();





#endif //UI_H