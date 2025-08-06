#include "globals.h"
#include "circuit_ui.h"
#include "utils.h"
#include "factory.h"
#include "program.h"
#include "ui.h"
#include "handle.h"
#include <ncurses.h>
#include "command_console.h"

#define FRAME_RATE 32
#define MIN_ROWS 30
#define MIN_COLS 150

bool check_fullscreen() {
    int rows, cols;

    initscr();            
    noecho();
    curs_set(0);

    getmaxyx(stdscr, rows, cols);  

    clear();

    if (rows < MIN_ROWS || cols < MIN_COLS) {
        mvprintw(rows/2, (cols - 30)/2, "Please turn on full screen!");
        refresh();

        napms(30);
        check_fullscreen();  
    } 
}
void run_program() {
    init_all_extern_globals();
    clear_logger_file(global_logger);
    MEVENT event;
    int ch;
    while(global_program->program_running) {
        check_fullscreen();
        box(stdscr, 0, 0);
        ch = getch();
        
        if(ch == KEY_MOUSE) {
            if(getmouse(&event) == OK) {
                mouse_handle(event);
            } else {
                log_message(global_logger, ERROR, "invalid mouse event received");
                continue;
            }
        } else {
            keyboard_handle(ch);
        }
        
        if(global_program->program_state == ProgramStateExiting) {
            log_message(global_logger, INFO, "The program finished successfully");
            break;
        }
        if(global_program->program_state == ProgramStateMenu) {
            draw_menu();
            refresh();
        }else if(global_program->program_state == ProgramStateCircuitProccess) {
            draw_grid();
            init_command_console();
            refresh();   
        }/* else if(global_program->program_state == ProgramStateLogger) {
            
        } else if(global_program->program_state == ProgramStateSettings) {
            
        } todo */
        
        napms(FRAME_RATE);
        clear(); //napms - threadsleep 
    }
    free_program(global_program);
    kill_terminal();
}