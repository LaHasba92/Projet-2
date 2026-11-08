#include <iostream>
#include "Player.h"

Player::Player(Vector2 position, int health)
	: Entity(position, health)
{
}

void Player::onCollision(Entity* other)
{
}

void Player::onUpdate(const Map& map, Entity* player)
{
}

void Player::readPlayerInputs(const Map& map)
{
	Vector2 direction(0, 0);
	GetDirection(direction);
	if (direction.getX() != 0 || direction.getY() != 0)
	{
		move(direction, map);
	}
}

void Player::GetDirection(Vector2& direction) const
{
    std::string touche;
    std::cin >> touche;

    switch (touche[0])
    {
    case 'z':
        direction.setY(-1);
        break;

    case 's':
        direction.setY(1);
        break;

    case 'q':
        direction.setX(-1);
        break;

    case 'd':
        direction.setX(1);
        break;
    }
}

