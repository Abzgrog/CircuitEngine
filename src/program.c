#include "globals.h"
#include "factory.h"
#include "program.h"
#include "ui.h"
#include <ncurses.h>

void run_program() {
    init_all_extern_globals();

    if(global_program) {
        while (global_program->program_running) {
            if(global_program->program_state == ProgramStateMenu) {
                printf("llll");
                draw_and_init_buttons();
            }
            if(global_program->program_state == ProgramStateSettings) {
                
            }
            if(global_program->program_state == ProgramStateCircuitProccess) {
    
            }
        }
    }
    
}