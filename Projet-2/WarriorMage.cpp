#include "WarriorMage.h"
#include <cstdlib>

WarriorMage::WarriorMage(Vector2 position)
    : Player(position, MAX_HEALTH)
{
}

void WarriorMage::onUpdate()
{
    // Mise à jour spécifique au WarriorMage.
}

void WarriorMage::onCollision(Entity* other)
{
    // La logique de collision sera complétée
    // avec le système de combat.
}

void WarriorMage::attackMelee(Entity* target)
{
    if (target == nullptr || !target->isAlive())
        return;

    Vector2 myPosition = getPosition();
    Vector2 targetPosition = target->getPosition();

    int distance =
        std::abs(myPosition.getX() - targetPosition.getX()) +
        std::abs(myPosition.getY() - targetPosition.getY());

    // L'attaque au contact nécessite une case d'écart.
    if (distance != 1)
        return;

    target->applyDamage(MELEE_DAMAGE);
}

void WarriorMage::castSpell(Entity* target)
{
    if (target == nullptr || !target->isAlive())
        return;

    Vector2 myPosition = getPosition();
    Vector2 targetPosition = target->getPosition();

    int distance =
        std::abs(myPosition.getX() - targetPosition.getX()) +
        std::abs(myPosition.getY() - targetPosition.getY());

    // Le sort ne peut pas toucher à plus de 3 cases.
    if (distance == 0 || distance > SPELL_RANGE)
        return;

    target->applyDamage(SPELL_DAMAGE);
}