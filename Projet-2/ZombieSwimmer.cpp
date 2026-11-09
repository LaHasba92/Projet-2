#include "ZombieSwimmer.h"

#include <random>
#include <vector>

ZombieSwimmer::ZombieSwimmer(Vector2 position)
    : Enemy(position, MAX_HEALTH)
{
}

void ZombieSwimmer::onCollision(Entity* other)
{
    if (other == nullptr || !other->isAlive())
        return;

    other->applyDamage(ATTACK_DAMAGE);
}

void ZombieSwimmer::onUpdate(const Map& map, Entity* player)
{
    // Le ZombieSwimmer se déplace aléatoirement.
    static std::random_device rd;
    static std::mt19937 generateur(rd());

    const Vector2 directions[4] =
    {
        Vector2(0, -1),
        Vector2(0, 1),
        Vector2(-1, 0),
        Vector2(1, 0)
    };

    std::vector<Vector2> mouvementsPossibles;
    Vector2 position = getPosition();

    for (const Vector2& direction : directions)
    {
        Vector2 nouvellePosition = position + direction;

        if (map.isWalkable(nouvellePosition) ||
            map.isSwimmable(nouvellePosition))
        {
            mouvementsPossibles.push_back(direction);
        }
    }

    if (mouvementsPossibles.empty())
        return;

    std::uniform_int_distribution<int> distribution(
        0,
        static_cast<int>(mouvementsPossibles.size()) - 1
    );

    Vector2 directionChoisie = mouvementsPossibles[distribution(generateur)];
    Vector2 prochainePosition = position + directionChoisie;

    // Gestion de l'oxygène.
    if (map.isSwimmable(prochainePosition))
    {
        if (oxygen > 0)
            oxygen--;
        else
            applyDamage(1);
    }
    else
    {
        oxygen = MAX_OXYGEN;
    }

    moveSwimming(directionChoisie, map);
}