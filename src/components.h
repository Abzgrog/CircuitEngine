#ifndef COMPONENTS.H
#define COMPONENTS.H

#include <stdbool.h>
typedef struct Component {
    char name[20];
    int x;
    int y;
    int length;
    Node node1;
    Node node2; 
    Node node3;
    double power;
    double value;
    void (*action)(struct Component*, int);
    ComponentState state;
    ComponentType type;
} Component;
typedef enum ComponentType {
    RESISTOR,
    WIRE,
    LED,
    VOLTAGE_SOURCE,
    SWITCH
} ComponentType;
typedef struct Node {
    int x;
    int y;
} Node;
typedef struct ComponentState {
    bool enabled;
    bool energized;
} ComponentState;

#endif //COMPONENTS.H