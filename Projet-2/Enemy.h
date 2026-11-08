#pragma once
#include "Entity.h"

class Enemy : public Entity
{
public:
    Enemy(Vector2 position, int health);

    void onCollision(Entity* other) override;
    void onUpdate() override;
};
