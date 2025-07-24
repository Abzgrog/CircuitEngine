#ifndef FACTORY_H
#define FACTORY_H

#include "components.h"

Component* create_component(ComponentType type, int x, int y);

#endif //FACTORY_H