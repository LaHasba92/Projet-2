#pragma once

#include "Map.h"
#include "Utilities.h"

// Classe parent commune au joueur et aux ennemis.
class Entity
{
public:
    Entity(Vector2 position, int health);
    virtual ~Entity() = default;

    // Ces fonctions seront définies par Player et Enemy.
    virtual void onCollision(Entity* other) = 0;
    virtual void onUpdate(const Map& map, Entity* player) = 0;

    // Déplace l'entité si la case est accessible.
    bool move(Vector2 direction, const Map& map);
    bool move(Vector2 direction, const Map& map, bool canSwim);


    // Retire des points de vie.
    void applyDamage(int damage);

    // Renvoie des informations sans exposer les attributs privés.
    int getHealth() const;
    bool isAlive() const;
    Vector2 getPosition() const;

private:
    Vector2 position{};
    int health = 1;
    bool alive = true;
};