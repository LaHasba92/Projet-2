#pragma once
#include <vector2>

class Entity {
	Vector2 position;
	int vie;
	bool vivant;
};

Entity Move(Entity entity, Vector2 direction) {
	entity.position += direction;
}

Entity ApplyDamage(Entity entity, int damage) {
	entity.vie -= damage;
	if (entity.vie <= 0) {
		entity.vivant = false;
	}
}

Entity OnCollision(Entity entity, Entity autre) {
	pass;
}

Entity OnUpdate(Entity entity) {
	entity.move(entity.position);
	entity.applyDamage(entity.vie);
	entity.onCollision(entity, autre);
}