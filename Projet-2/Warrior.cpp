#include "Warrior.h"

Warrior::Warrior(Vector2 position)
    : Player(position, MAX_HEALTH)
{
}

void Warrior::onUpdate()
{
    // Mise à jour spécifique au Warrior.
}

void Warrior::onCollision(Entity* other)
{
    // À compléter avec la logique d'identification
    // des ennemis et l'application des dégâts.
}

void Warrior::attack(Entity* target)
{
    if (target == nullptr || !target->isAlive())
    {
        return;
    }

    target->applyDamage(ATTACK_DAMAGE);
}