#ifndef GLOBAL_H
#define GLOBAL_H

#include "components.h"
#include "circuit.h"
#include "program.h"
#include "factory.h"
#define MAX_COMPONENTS 100
#define BUFFER_WIDTH 50
#define BUFFER_HEIGHT 30

extern Program* global_program;
void init_all_extern_globals();

#endif //GLOBAL_H