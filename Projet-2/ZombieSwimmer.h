#pragma once
#include "Enemy.h"

class ZombieSwimmer : public Enemy
{
public:
    ZombieSwimmer(Vector2 position);

    void onCollision(Entity* other) override;
    void onUpdate(const Map& map, Entity* player) override;

private:
    static constexpr int MAX_HEALTH = 2;
    static constexpr int ATTACK_DAMAGE = 1;
    static constexpr int MAX_OXYGEN = 3;

    int oxygen = MAX_OXYGEN;
};