#pragma once
#include "Utilities.h"

class Entity
{
public:
    Vector2 position{};
    int vie = 100;
    bool vivant = true;
};

inline Entity Move(Entity entity, Vector2 direction)
{
    entity.position.x += direction.x;
    entity.position.y += direction.y;
    return entity;
}

inline Entity ExecuteAction(Entity entity, Vector2 direction, int damage)
{
	return entity;
}

inline Entity ApplyDamage(Entity entity, int damage)
{
    entity.vie -= damage;
    return entity;
}

inline Entity CheckDeath(Entity entity)
{
	if (entity.vie <= 0)
		entity.vivant = false;
	return entity;
}

inline Entity OnCollision(Entity entity, const Entity& autre)
{
    // À compléter quand le comportement des collisions sera défini.
    (void)autre;
    return entity;
}

inline Entity OnUpdate(Entity entity, Vector2 direction, int damage)
{
	entity.Move(entity, direction);
	entity.CheckDeath(entity);
    return entity;
}