#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "components.h"
#include "globals.h"
#include <stdlib.h>

void none();

typedef struct Circuit {
    CircuitComponent* components[MAX_COMPONENTS];
    int count_components;
    bool enabled;
} Circuit;

void update_circuit(Circuit* c);
void circuit_loop(Circuit* c);
Circuit* init_circuit();
#endif //CIRCUIT_H