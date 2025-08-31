#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#include <ncurses.h>

void draw_square_grid(int start_y, int start_x, int square_height, int square_width, int rows, int cols) {
    wattron(stdscr, A_BOLD | COLOR_PAIR(1));
    for (int c = 0; c < cols; c++) {
        int x = start_x + c * square_width + square_width / 2;
        char ch = (c < 10) ? ('0' + c) : ('A' + (c - 10));
        mvwaddch(stdscr, start_y - 1, x, ch);
    }

    for (int r = 0; r < rows; r++) {
        int y = start_y + r * square_height + square_height / 2; 
        char ch = (r < 10) ? ('0' + r) : ('A' + (r - 10));
        mvwaddch(stdscr, y, start_x - 2, ch);
    }
    wattroff(stdscr, A_BOLD | COLOR_PAIR(1));

    wattron(stdscr, A_BOLD | COLOR_PAIR(3));
    // Рисуем квадраты
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int y = start_y + r * square_height;
            int x = start_x + c * square_width;

            // Верхняя строка
            mvwaddch(stdscr, y, x, ACS_ULCORNER);
            for (int i = 1; i < square_width - 1; i++)
                mvwaddch(stdscr, y, x + i, ACS_HLINE);
            mvwaddch(stdscr, y, x + square_width - 1, ACS_URCORNER);

            // Боковые линии
            for (int i = 1; i < square_height - 1; i++) {
                mvwaddch(stdscr, y + i, x, ACS_VLINE);
                for (int j = 1; j < square_width - 1; j++)
                    mvwaddch(stdscr, y + i, x + j, ' '); 
                mvwaddch(stdscr, y + i, x + square_width - 1, ACS_VLINE);
            }

            // Нижняя строка
            mvwaddch(stdscr, y + square_height - 1, x, ACS_LLCORNER);
            for (int i = 1; i < square_width - 1; i++)
                mvwaddch(stdscr, y + square_height - 1, x + i, ACS_HLINE);
            mvwaddch(stdscr, y + square_height - 1, x + square_width - 1, ACS_LRCORNER);
        }
    }

    wattroff(stdscr, A_BOLD | COLOR_PAIR(3));
}