#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdbool.h>    

struct Circuit;

typedef enum ProgramState {
    ProgramStateMenu,
    ProgramStateSettings,
    ProgramStateCircuitProccess,
    ProgramStateExiting,
    ProgramStateLogger
} ProgramState;
typedef struct Program {
    bool program_running;
    ProgramState program_state;
    struct Circuit* circuit;
} Program;


void run_program();

#endif //PROGRAM_H