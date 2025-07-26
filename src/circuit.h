#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "components.h"
#include "globals.h"
#include <stdlib.h>

void none();
Circuit* init_circuit();
void update_circuit(Circuit* c);
void circuit_loop(Circuit* c);


typedef struct Circuit {
    CircuitComponent* components[MAX_COMPONENTS];
    bool enabled;
} Circuit;

#endif //CIRCUIT_H