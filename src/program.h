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
    char** prev_frame_program_buffer;
} Program;


void run_program();
char** get_program_buffer();
void copy_buffer(char **dest, char **src, int height, int width);
bool buffers_equal(char **a, char **b, int height, int width);

#endif //PROGRAM_H