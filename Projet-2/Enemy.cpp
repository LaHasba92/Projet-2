#include "Enemy.h"

Enemy::Enemy(Vector2 position, int health)
    : Entity(position, health)
{
}

void Enemy::onCollision(Entity* other)
{
}

void Enemy::onUpdate(const Map& map, Entity* player)
{
}