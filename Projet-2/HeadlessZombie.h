#pragma once
#include "Enemy.h"

class HeadlessZombie : public Enemy
{
public:
    HeadlessZombie(Vector2 position);

    void onCollision(Entity* other) override;
    void onUpdate(const Map& map, Entity* player) override;

private:
    static constexpr int MAX_HEALTH = 2;
    static constexpr int ATTACK_DAMAGE = 1;
};