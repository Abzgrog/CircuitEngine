#include "globals.h"
#include "factory.h"

Program* global_program;

void init_all_extern_globals() {
   global_program = create_program();
}