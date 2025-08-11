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

// Checks if the terminal window is large enough.
// This is called when the program starts and when the window is resized.
bool check_fullscreen() {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    if (rows < MIN_ROWS || cols < MIN_COLS) {
        // 'clear()' is acceptable here because this is a special state outside the main render loop.
        clear(); 
        mvprintw(rows/2, (cols - 30)/2, "Please turn on full screen!");
        refresh();
        return false;
    }
    return true;
}

// Main function to run the program's primary loop.
void run_program() {
    init_all_extern_globals();
    clear_logger_file(global_logger);

    MEVENT event;
    int ch;

    // Make getch() non-blocking.
    // It will return ERR immediately if there is no input, instead of waiting.
    nodelay(stdscr, TRUE);

    // Initial check to ensure screen size is correct before starting the main loop.
    while (!check_fullscreen()) {
        napms(100); // Wait for the user to resize the window.
    }

    // --- Main Program Loop ---
    while (global_program->program_running) {
        
        // ----- 1. Process Input -----
        ch = getch();

        // Handle terminal resize event.
        if (ch == KEY_RESIZE) {
            // Re-check screen size if the window was resized.
            while (!check_fullscreen()) {
                napms(100);
            }
        }
        
        if (ch == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                mouse_handle(event);
            } else {
                log_message(global_logger, ERROR, "invalid mouse event received");
            }
        } else if (ch != ERR) { // An actual key was pressed.
            keyboard_handle(ch);
        }

        if (global_program->program_state == ProgramStateExiting) {
            log_message(global_logger, INFO, "The program finished successfully");
            break;
        }

        // ----- 2. Draw Frame -----
        
        // Clear the virtual screen (buffer) in preparation for the new frame.
        // This does not touch the physical screen, preventing flicker.
        erase();

        box(stdscr, 0, 0);

        if (global_program->program_state == ProgramStateMenu) {
            draw_menu();
        } else if (global_program->program_state == ProgramStateCircuitProccess) {
            draw_grid();
            init_command_console();
        }

        // Atomically update the physical screen from the virtual screen.
        // ncurses calculates the minimal changes needed and sends them to the terminal.
        refresh();

        // ----- 3. Control Frame Rate -----
        
        // Pause at the END of the loop to maintain a consistent frame rate.
        // The user sees the completed frame during this pause.
        napms(FRAME_RATE);
    }

    free_program(global_program);
    kill_terminal();
}