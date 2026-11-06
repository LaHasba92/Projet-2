<<<<<<< HEAD
=======
#pragma once
#include "Player.h"

class Warrior : public Player
{
public:
    Warrior(Vector2 position);

    void onCollision(Entity* other) override;
    void onUpdate() override;

private:
    static constexpr int MAX_HEALTH = 150;
    static constexpr int ATTACK_DAMAGE = 20;

    void attack(Entity* target);
};
>>>>>>> Player
