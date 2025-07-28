#include "circuit.h"
#include "factory.h"

void none() {
    return;
}

Circuit* init_circuit() {
    Circuit* c = create_circuit();
    return c;
}



