#ifndef UTILS_H
#define UTILS_H

#include <ncurses.h>
#include <stdbool.h>

#define ERROR_HANDLING "Handling error!"
#define GET_WIDTH 120
#define GET_HEIGHT 121
#define ALLOC_STRUCT(type) \
    (type*)malloc(sizeof(type))


extern int WIN_WIDTH;
extern int WIN_HEIGHT;

void update_window_size(); // This function will update global WIN_WIDTH and WIN_HEIGHT
int get_current_window_size(int type);
bool string_array_equals(char** strarr, char** strarr2);
void kill_terminal();
void print_in_center(char string[]);
long long get_current_time_ms();
typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_RIGHT,
    UP_LEFT,
    DOWN_RIGHT,
    DOWN_LEFT,
    NONE_DIRECTION
} Direction;

#endif //UTILS_H