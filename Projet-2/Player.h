#pragma once
#include <iostream>
#include "Entity.h"

enum class Action
{
    Aucune,
    Haut,
    Bas,
    Gauche,
    Droite
};

class Player : public Entity
{
public:
    Action ReadPlayerInputs()
    {
        char touche{};
        std::cout << "Direction (z/q/s/d), puis Entree : ";

        if (!(std::cin >> touche))
            return Action::Aucune;

        switch (touche)
        {
        case 'z':
        case 'Z':
            return Action::Haut;
        case 's':
        case 'S':
            return Action::Bas;
        case 'q':
        case 'Q':
            return Action::Gauche;
        case 'd':
        case 'D':
            return Action::Droite;
        default:
            return Action::Aucune;
        }
    }

    Vector2 GetDirections(Action action) const
    {
        Vector2 direction{};

        switch (action)
        {
        case Action::Haut:
            direction.y = -1;
            break;
        case Action::Bas:
            direction.y = 1;
            break;
        case Action::Gauche:
            direction.x = -1;
            break;
        case Action::Droite:
            direction.x = 1;
            break;
        case Action::Aucune:
            break;
        }

        return direction;
    }
};

inline Player OnUpdate(Player player)
{
    const Action action = player.ReadPlayerInputs();
    const Vector2 direction = player.GetDirections(action);

    player.position.x += direction.x;
    player.position.y += direction.y;

    return player;
}