#include "factory.h"

Component* create_component(ComponentType type, int x, int y) {
    Component* component = malloc(sizeof(Component));

    switch (type)
    {
    case RESISTOR:
        break; 
    case WIRE:
        break;
    default: return;
    } 
}