#ifndef FACTORY_H
#define FACTORY_H

#include "circuit.h"

CircuitComponent* create_component(ComponentType type, int x, int y, void (*action)(struct CircuitComponent*, int));
Circuit* create_circuit();
Program* create_program();


#endif //FACTORY_H