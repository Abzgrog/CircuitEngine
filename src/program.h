#ifndef PROGRAM_H
#define PROGRAM_H
#include "circuit.h"

typedef struct Program {
    bool program_running;
    ProgramState program_state;
    Circuit* circuit;
} Program;

typedef enum ProgramState {
    ProgramStateMenu,
    ProgramStateSettings,
    ProgramStateCircuitProccess
} ProgramState;

void run_program();

#endif //PROGRAM_H