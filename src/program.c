#include "globals.h"
#include "utils.h"
#include "factory.h"
#include "program.h"
#include "ui.h"
#include "handle.h"
#include <ncurses.h>
#define FRAME_RATE 16

void run_program() {
    init_all_extern_globals();
    clear_logger_file(global_logger);
    MEVENT event;
    int ch;
    while(global_program->program_running) {
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
        }/*else if(global_program->program_state == ProgramStateCircuitProccess) {
            
        } else if(global_program->program_state == ProgramStateLogger) {
            
        } else if(global_program->program_state == ProgramStateSettings) {
            
        } todo */
        
        napms(FRAME_RATE);
        clear(); //napms - threadsleep 
    }
    free_program(global_program);
    kill_terminal();
}