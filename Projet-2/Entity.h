#pragma once
#include "Utilities.h"

struct Entity {
public:
    Vector2 position;
    int vie;
    bool vivant;
};

inline Entity Move(Entity entity, Vector2 direction) {
    entity.position = entity.position + direction;
    return entity;
}

inline Entity ApplyDamage(Entity entity, int damage) {
    entity.vie -= damage;j'ai mal'

    if (entity.vie <= 0) {
        entity.vivant = false;
    }

    return entity;
}

inline Entity OnCollision(Entity entity, Entity autre) {
    return entity;
}

inline Entity OnUpdate(Entity entity, Vector2 direction, Entity autre) {
    entity = Move(entity, direction);
    entity = OnCollision(entity, autre);

    return entity;
}