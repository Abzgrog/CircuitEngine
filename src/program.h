#ifndef PROGRAM_H
#define PROGRAM_H
#include "circuit.h"

typedef struct Program {
    ProgramState program_state;
    Circuit* circuit;
} Program;

typedef enum ProgramState {
    Menu,
    Settings,
    CircuitProccess
} ProgramState;

void run_program();

#endif //PROGRAM_H