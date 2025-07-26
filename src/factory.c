#include "factory.h"
#include "circuit.h"
#include "program.h"
#include <stdlib.h>

CircuitComponent* create_component(ComponentType type, int x, int y, void (*action)(struct CircuitComponent*, int)) {
    CircuitComponent* component = malloc(sizeof(CircuitComponent));
    component->type = type;
    component->x = x;
    component->y = y;
    component->state.enabled = false;
    component->state.energized = false;
    component->action = none;

    switch (type)
    {
    case RESISTOR:
        component->value = 120; //OM
        return component;
        break; 
    case WIRE:
        break;
    default: return;
    }
}

Circuit* create_circuit() {
    Circuit* c = malloc(sizeof(Circuit));
    if(c == NULL) {
        return NULL;
    }
    c->enabled = false;
    c->components[0] = NULL;
    return c; 
}

Program* create_program() {
    Program* program = malloc(sizeof(Program));
    if(program == NULL) {
        return NULL;
    }
    program->circuit = init_circuit();
    program->program_state = Menu;
    return program;
}