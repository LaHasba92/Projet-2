#pragma once
#include "Entity.h"

class Swimmer
{
public:
    bool swim(Entity& entity, Vector2 direction, const Map& map) const;
};