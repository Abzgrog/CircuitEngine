#include "ui.h"
#include "utils.h"
#include "factory.h"
#include "globals.h"
#include "logger.h"
#include <ncurses.h>
#include <string.h>

MenuButtons* get_menu_buttons() {
    MenuButtons* mb = create_menu_buttons(); 
    return mb;
}
void draw_button_extra(Button* b) {
    int x, y;
    int left_offset = 1;
    int right_offset = strlen(b->name);

    x = b->x;
    y = b->y;
    attron(COLOR_PAIR(1));
    mvaddch(y, x - left_offset, '>');
    mvaddch(y, x + right_offset, '<');
    attroff(COLOR_PAIR(1));

}
void clear_button_extra(Button* b) {
    int x, y;
    int left_offset = 1;
    int right_offset = strlen(b->name);

    x = b->x;
    y = b->y;

    mvaddch(y, x - left_offset, ' ');
    mvaddch(y, x + right_offset, ' ');
}
void draw_menu() {
    MenuButtons* mb = get_menu_buttons(); // mb is a static struct, when we draw buttons many times, struct DONT creating everytime
    int y_offset = 0;
    int win_width = get_current_window_size(GET_WIDTH);
    int win_height = get_current_window_size(GET_HEIGHT);
    int center_width = win_width / 2;
    int center_height = win_height / 2;
    
    attron(COLOR_PAIR(1));
    for(int i = MENU_BUTTONS_COUNT - 1; i >= 0; i--) {
        mb->buttons[i]->x = center_width;
        mb->buttons[i]->y = center_height;
        y_offset+=2;
        if(mb->buttons[i]->selected) {
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(2));
            
            mb->buttons[i]->y = mb->buttons[i]->y - y_offset;
            mb->buttons[i]->x = mb->buttons[i]->x - strlen(mb->buttons[i]->name) / 2;

            mvprintw(mb->buttons[i]->y, mb->buttons[i]->x, "%s", mb->buttons[i]->name);
            attroff(COLOR_PAIR(2));
            draw_button_extra(mb->buttons[i]);
            attron(COLOR_PAIR(1));
            continue;
        }
        mvprintw(mb->buttons[i]->y - y_offset, mb->buttons[i]->x - strlen(mb->buttons[i]->name) / 2, "%s", mb->buttons[i]->name);
    }
    attroff(COLOR_PAIR(1));
    getch();
}
