#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdbool.h>

// Предварительное объявление вместо включения заголовочного файла
struct Circuit;

typedef enum ProgramState {
    ProgramStateMenu,
    ProgramStateSettings,
    ProgramStateCircuitProccess
} ProgramState;
typedef struct Program {
    bool program_running;
    ProgramState program_state;
    struct Circuit* circuit;
} Program;


void run_program();

#endif //PROGRAM_H