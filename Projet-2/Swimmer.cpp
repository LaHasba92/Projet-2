#include "Swimmer.h"

bool Swimmer::swim(Entity& entity, Vector2 direction, const Map& map) const
{
    return entity.move(direction, map, true);
}