#include "HeadlessZombie.h"

#include <random>
#include <vector>

HeadlessZombie::HeadlessZombie(Vector2 position)
    : Enemy(position, MAX_HEALTH)
{
}

void HeadlessZombie::onCollision(Entity* other)
{
    if (other == nullptr || !other->isAlive())
        return;

    other->applyDamage(ATTACK_DAMAGE);
}

void HeadlessZombie::onUpdate(const Map& map, Entity* player)
{
    // Le HeadlessZombie ne poursuit pas le joueur.
    // Il se déplace aléatoirement.

    static std::random_device rd;
    static std::mt19937 generateur(rd());

    const Vector2 directions[4] =
    {
        Vector2(0, -1),  // Haut
        Vector2(0, 1),   // Bas
        Vector2(-1, 0),  // Gauche
        Vector2(1, 0)    // Droite
    };

    std::vector<Vector2> mouvementsPossibles;

    Vector2 position = getPosition();

    // Récupère les déplacements autorisés.
    for (const Vector2& direction : directions)
    {
        Vector2 nouvellePosition = position + direction;

        if (map.isWalkable(nouvellePosition))
        {
            mouvementsPossibles.push_back(direction);
        }
    }

    // Aucun déplacement possible.
    if (mouvementsPossibles.empty())
        return;

    // Choisit un déplacement aléatoire.
    std::uniform_int_distribution<int> distribution(
        0,
        static_cast<int>(mouvementsPossibles.size()) - 1
    );

    int choix = distribution(generateur);

    move(mouvementsPossibles[choix], map);
}