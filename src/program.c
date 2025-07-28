#include "globals.h"
#include "factory.h"

void run_program() {
    init_all_extern_globals();

    if(global_program != NULL) {
        while (global_program->program_running == true) {
            if(global_program->program_state == ProgramStateMenu) {
                
            }
            if(global_program->program_state == ProgramStateSettings) {
                
            }
            if(global_program->program_state == ProgramStateCircuitProccess) {
    
            }
        }
    }
    
}