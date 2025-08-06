#include <ncurses.h>
#include "program.h"
#include "factory.h"
#include "globals.h"
#define MIN_ROWS 30
#define MIN_COLS 100

bool check_fullscreen();

void initNcurses() {
    initscr();
    start_color();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    curs_set(0);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
}

int main() {
    initNcurses();
       
    run_program();
    
    endwin();
}
