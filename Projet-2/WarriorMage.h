<<<<<<< HEAD
=======
#pragma once
#include "Player.h"

class WarriorMage : public Player
{
public:
    WarriorMage(Vector2 position);

    void onCollision(Entity* other) override;
    void onUpdate() override;

    void attackMelee(Entity* target);
    void castSpell(Entity* target);

private:
    static constexpr int MAX_HEALTH = 125;
    static constexpr int MELEE_DAMAGE = 15;
    static constexpr int SPELL_DAMAGE = 15;
    static constexpr int SPELL_RANGE = 3;
};
>>>>>>> Player
