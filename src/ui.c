#include "ui.h"
#include "utils.h"
#include "factory.h"
#include <ncurses.h>

void draw_menu() {

}
void draw_and_init_buttons() {
    MenuButtons* mb = create_menu_buttons();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));
    for(int i = 0; i < MENU_BUTTONS_COUNT; i++) {
        mvprintw(mb->buttons[i]->y, mb->buttons[i]->x, "%s", mb->buttons[i]->name);
    }
    attroff(COLOR_PAIR(1));
    getch();
}
