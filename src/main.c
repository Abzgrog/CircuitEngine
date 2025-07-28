#include <ncurses.h>
#include "program.h"
#include "factory.h"
#include "globals.h"

void initNcurses() {
    initscr();
    start_color();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

int main() {
    initNcurses();
    
    run_program();
    
    endwin();
}
