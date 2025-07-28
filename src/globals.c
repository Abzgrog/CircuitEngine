#include "globals.h"
#include "factory.h"
#include "program.h"

struct Program* global_program;

void init_all_extern_globals() {
   global_program = create_program();
}