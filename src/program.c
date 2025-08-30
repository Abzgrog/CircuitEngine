#include "globals.h"
#include "circuit_ui.h"
#include "utils.h"
#include "factory.h"
#include "program.h"
#include "ui.h"
#include "handle.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "command_console.h"

#define FRAME_RATE 32
#define MIN_ROWS 30
#define MIN_COLS 150

bool check_fullscreen() {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    if (rows < MIN_ROWS || cols < MIN_COLS) {
        clear();
        mvprintw(rows/2, (cols - 30)/2, "Please turn on full screen!");
        refresh();
        return false;
    }
    return true;
}

void run_program() {
    MEVENT event;
    int ch1 = ERR;
    int ch_command_console = ERR;

    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    while (!check_fullscreen()) {
        napms(100);
    }

    if (global_program->command_console && global_program->command_console->win) {
        nodelay(global_program->command_console->win, TRUE);
        keypad(global_program->command_console->win, TRUE);
    }

    // --- Main Program Loop ---
    while (global_program->program_running) {

        // ----- 1. Process Input -----
        if (global_program->current_window == MainWindow) {
            ch1 = wgetch(stdscr);
        } else {
            ch1 = ERR;
        }

        if (global_program->command_console && global_program->command_console->win &&
            (global_program->current_window == CommandWindow ||
             global_program->program_state == ProgramStateCircuitProccess)) {

            ch_command_console = wgetch(global_program->command_console->win);

            if (ch_command_console != ERR) {
                char buf[128];
                snprintf(buf, sizeof(buf), "Pressed key (CLI) = %s", get_key_name_by_id(ch_command_console));
                log_message(global_loger, DEBUG, buf);
                keyboard_handle(ch_command_console);
            }
        } else {
            ch_command_console = ERR;
        }

        // Handle terminal resize event.
        if (ch1 == KEY_RESIZE || ch_command_console == KEY_RESIZE) {
            // Re-check screen size if the window was resized.
            while (!check_fullscreen()) {
                napms(100);
            }
        }

        if (ch1 == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                mouse_handle(event);
            } else {
                log_message(global_loger, ERROR, "invalid mouse event received");
            }

        } else if (ch1 != ERR) {
            char buf[128];
            snprintf(buf, sizeof(buf), "Pressed key (MAIN) = %s", get_key_name_by_id(ch1));
            log_message(global_loger, DEBUG, buf);
            keyboard_handle(ch1);
        }

        if (global_program->program_state == ProgramStateExiting) {
            break;
        }

        // ----- 2. Draw Frame -----
        werase(stdscr);
        //box(stdscr, 'X', 'x');
        wborder(stdscr,
        '|', '|',    // левая/правая граница
        '-', '-',    // верх/низ
        '+', '+',    // верхние углы
        '+', '+');  

        if (global_program->program_state == ProgramStateMenu) {
            draw_menu();
        } else if (global_program->program_state == ProgramStateCircuitProccess) {
            if (global_program->current_window != CommandWindow) {
                global_program->current_window = CommandWindow;
            }
            draw_grid();
          //  draw_command_console_buffer(global_program->command_console, );
        }


        update_panels();
        doupdate();

        // ----- 3. Control Frame Rate -----
        napms(FRAME_RATE);
    }

    free_program(global_program);
    log_message(global_loger, INFO, "The program finished successfully");
    kill_terminal();
}