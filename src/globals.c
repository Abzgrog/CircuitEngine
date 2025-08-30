#include "globals.h"
#include "factory.h"
#include "program.h"

struct Logger* global_loger;
struct Program* global_program;

void init_all_extern_globals() {
   global_loger = create_logger();
   global_program = create_program();
}