#include "Zombie.h"
#include <cstdlib>

Zombie::Zombie(Vector2 position)
    : Enemy(position, MAX_HEALTH)
{
}

void Zombie::onCollision(Entity* other)
{
    if (other == nullptr || !other->isAlive())
        return;

    other->applyDamage(ATTACK_DAMAGE);
}

void Zombie::onUpdate(const Map& map, Entity* player)
{
    if (player == nullptr || !player->isAlive())
        return;

    Vector2 direction = getNextDirection(player);

    move(direction, map);
}

Vector2 Zombie::getNextDirection(Entity* player) const
{
    Vector2 myPosition = getPosition();
    Vector2 playerPosition = player->getPosition();

    int differenceX = playerPosition.getX() - myPosition.getX();
    int differenceY = playerPosition.getY() - myPosition.getY();

    if (std::abs(differenceX) >= std::abs(differenceY))
    {
        if (differenceX > 0)
            return Vector2(1, 0);

        if (differenceX < 0)
            return Vector2(-1, 0);
    }

    if (differenceY > 0)
        return Vector2(0, 1);

    if (differenceY < 0)
        return Vector2(0, -1);

    return Vector2(0, 0);
}