#ifndef FACTORY_H
#define FACTORY_H

#include "components.h"
#include "ui.h"
#include <stdbool.h>

// Предварительные объявления
struct Circuit;
struct Program;

typedef struct Circuit Circuit;
typedef struct Program Program;

CircuitComponent* create_component(ComponentType type, int x, int y, void (*action)(struct CircuitComponent*, int));
Circuit* create_circuit();
Program* create_program();
Button* create_button(int x, int y, char* name);
MenuButtons* create_menu_buttons();

void free_button(Button* b);
void free_menu_buttons(MenuButtons* mb);
void free_circuit(Circuit* c);
void free_circuit_component(CircuitComponent* c);
void free_program(Program* p);




#endif //FACTORY_H