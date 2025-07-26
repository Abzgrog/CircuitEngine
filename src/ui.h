#ifndef UI_H
#define UI_H

#include "components.h"
#include "globals.h"

typedef struct Screen {
    char buffer[BUFFER_HEIGHT][BUFFER_WIDTH];
} Screen;

void draw_component();
void draw_all_components();

#endif //UI_H