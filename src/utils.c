#include "common.h"
#include "ui.h"
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define GET_WIDTH 120
#define GET_HEIGHT 121

static void update_window_size(int width, int height) {
    width = getmaxy(stdscr);
    height  = getmaxx(stdscr);
}
int get_current_window_size(int type) { 
    int WIN_WIDTH = 0;
    int WIN_HEIGHT = 0;
    
    update_window_size(WIN_WIDTH, WIN_HEIGHT);

    switch (type)
    {
    case 120:
        return WIN_WIDTH;
    case 121:
        return WIN_HEIGHT;
        default: return;
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
