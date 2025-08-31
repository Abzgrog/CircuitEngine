#include "utils.h"
#include "ui.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define __MAX_KEY_NAME_LEN 20

int WIN_WIDTH;
int WIN_HEIGHT;

char* get_key_name_by_id(int key) {
    switch(key) {
        case 27: 
            return "ESC";
        case '\n': 
            return "ENTER";
        case KEY_F(2):
            return "F2";
        case KEY_UP:
            return "UP";
        case KEY_DOWN:
            return "DOWN";
        default: {
            static char buf[__MAX_KEY_NAME_LEN];
            snprintf(buf, __MAX_KEY_NAME_LEN, "%d", key);
            return buf;
        }
    }
}

void update_window_size() {
    WIN_HEIGHT = getmaxy(stdscr);
    WIN_WIDTH  = getmaxx(stdscr);
}
bool string_array_equals(char** strarr, char** strarr2) {
    int i = 0;
    
    while(strarr[i] != NULL && strarr2[i] != NULL) {
        int cmp = strcmp(strarr[i], strarr2[i]);

        if(cmp != 0) {
            return false;
        }

        if(strarr[i] == NULL && strarr2 == NULL) {
            return true;
        }
        
        if(strarr[i] == NULL || strarr2 == NULL) {
            return false;
        }
        i++;
    }

}
int get_current_window_size(int type) {
    update_window_size();

    switch (type)
    {
    case GET_WIDTH:
        return WIN_WIDTH;
    case GET_HEIGHT:
        return WIN_HEIGHT;
    default: return 0; // Return 0 for unknown type
    }
}
void print_in_center(char string[]) {
    int lenght = strlen(string);
    int WIN_WIDTH = get_current_window_size(GET_WIDTH);
    int WIN_HEIGHT = get_current_window_size(GET_HEIGHT);

    int x, y;
    y = WIN_HEIGHT / 2;
    x = (WIN_WIDTH - lenght) / 2;
    
    mvprintw(y, x, "%s", string);
    refresh();
}

void kill_terminal() {
    endwin();
    exit(0);
}

void print_helping_info(int x, int y) {
    attron(A_BOLD | COLOR_PAIR(1));
    mvwprintw(stdscr, y, x, "Type \"Help\" for more information about commands.\tType \"Cpt\" for get all types of component" );
    attroff(A_BOLD | COLOR_PAIR(1));
    
    attron(A_BOLD | COLOR_PAIR(1));
    mvwprintw(stdscr, y+2, x, "Type \"CpInfo\" for info about creating comp.\tType \"Run\" for start circuit!" );
    attroff(A_BOLD | COLOR_PAIR(1));
    
    attron(A_BOLD | COLOR_PAIR(1));
    mvwprintw(stdscr, y+4, x, "Type \"Stop\" for stop circuit work.\t\tGood Luck!" );
    attroff(A_BOLD | COLOR_PAIR(1));
}

long long get_current_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}