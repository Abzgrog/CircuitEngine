#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <stdbool.h>
typedef enum ComponentType {
    RESISTOR,
    WIRE,
    LED,
    VOLTAGE_SOURCE,
    SWITCH
} ComponentType;
typedef struct ComponentState {
    bool enabled;
    bool energized;
} ComponentState;
typedef struct Node {
    int x;
    int y;
} Node;
typedef struct CircuitComponent {
    char name[20];
    int x;
    int y;
    Node node1;
    Node node2; 
    Node node3;
    double power;
    double value;
    void (*action)(struct CircuitComponent*, int);
    ComponentState state;
    ComponentType type;
} CircuitComponent;

void update_component(CircuitComponent* comp);

#endif //COMPONENTS.H