<<<<<<< HEAD
=======
#pragma once
#include "Player.h"

class Mage : public Player
{
public:
    Mage(Vector2 position);

    void onCollision(Entity* other) override;
    void onUpdate() override;

    void attack(Entity* target);

private:
    static constexpr int MAX_HEALTH = 100;
    static constexpr int ATTACK_DAMAGE = 15;
    static constexpr int ATTACK_RANGE = 3;
};
>>>>>>> Player
