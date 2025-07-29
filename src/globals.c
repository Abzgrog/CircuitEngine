#include "globals.h"
#include "factory.h"
#include "program.h"

struct Program* global_program;
struct Logger* global_logger;

void init_all_extern_globals() {
   global_program = create_program();
   global_logger = create_logger();
}