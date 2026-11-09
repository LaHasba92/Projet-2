#include "Entity.h"

// Initialise les données reçues à la création de l'entité.
Entity::Entity(Vector2 startPosition, int startHealth)
    : position(startPosition),
    health(startHealth),
    alive(startHealth > 0)
{
}

// Calcule la prochaine position et vérifie le terrain avec Map.
bool Entity::move(Vector2 direction, const Map& map)
{
    return move(direction, map, false);
}

bool Entity::move(Vector2 direction, const Map& map, bool canSwim)
{
    Vector2 newPosition = position + direction;

    if (!map.isWalkable(newPosition) &&
        !(canSwim && map.isSwimmable(newPosition)))
        return false;

    position = newPosition;
    return true;
}

// Retire des points de vie et marque l'entité comme morte si nécessaire.
void Entity::applyDamage(int damage)
{
    if (damage <= 0 || !alive)
    {
        return;
    }

    health -= damage;

    if (health <= 0)
    {
        health = 0;
        alive = false;
    }
}

int Entity::getHealth() const
{
    return health;
}

bool Entity::isAlive() const
{
    return alive;
}

Vector2 Entity::getPosition() const
{
    return position;
}
