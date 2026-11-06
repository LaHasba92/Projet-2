#include "Mage.h"
#include <cstdlib>

Mage::Mage(Vector2 position)
    : Player(position, MAX_HEALTH)
{
}

void Mage::onUpdate()
{
    // Aucune mécanique supplémentaire.
}

void Mage::onCollision(Entity* other)
{
    // Le Mage attaque à distance.
    // Les collisions ne déclenchent donc pas son attaque.
}

void Mage::attack(Entity* target)
{
    if (target == nullptr || !target->isAlive())
    {
        return;
    }

    Vector2 magePosition = getPosition();
    Vector2 targetPosition = target->getPosition();

    int distance =
        std::abs(magePosition.getX() - targetPosition.getX()) +
        std::abs(magePosition.getY() - targetPosition.getY());

    if (distance > ATTACK_RANGE)
    {
        return;
    }

    target->applyDamage(ATTACK_DAMAGE);
}