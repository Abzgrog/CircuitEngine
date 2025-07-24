#include <ncurses.h>

void initNcurses() {
    initscr();           
    cbreak();            
    noecho();             
    keypad(stdscr, TRUE);
    curs_set(0);
}

int main() {
    initNcurses();

    
    endwin();
}
