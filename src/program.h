#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdbool.h>    
#include <ncurses.h>
#include "command_console.h"

struct Circuit;


typedef enum ProgramState {
    ProgramStateMenu,
    ProgramStateSettings,
    ProgramStateCircuitProccess,
    ProgramStateExiting,
    ProgramStateLogger
} ProgramState;
typedef enum CurrentWindow {
    MainWindow,
    CommandWindow
} CurrentWindow;
typedef struct Program {
    WINDOW* main_window;
    CommandConsole* command_console;
    bool program_running;
    CurrentWindow current_window;
    ProgramState program_state;
    struct Circuit* circuit;
    char** prev_frame_program_buffer;
} Program;


void run_program();
char** get_program_buffer();
void copy_buffer(char **dest, char **src, int height, int width);
bool buffers_equal(char **a, char **b, int height, int width);

#endif //PROGRAM_H