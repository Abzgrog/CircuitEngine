#include "utils.h"
#include "ui.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

int WIN_WIDTH;
int WIN_HEIGHT;

void update_window_size() {
    WIN_HEIGHT = getmaxy(stdscr);
    WIN_WIDTH  = getmaxx(stdscr);
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

void close_terminal() {
    endwin();
    exit(0);
}

long long get_current_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
