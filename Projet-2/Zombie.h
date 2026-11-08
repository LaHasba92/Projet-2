#pragma once
#include "Enemy.h"

class Zombie : public Enemy
{
public:
    Zombie(Vector2 position);

    void onCollision(Entity* other) override;
    void onUpdate(const Map& map, Entity* player) override;

private:
    static constexpr int MAX_HEALTH = 1;
    static constexpr int ATTACK_DAMAGE = 1;

    Vector2 getNextDirection(Entity* player) const;
};