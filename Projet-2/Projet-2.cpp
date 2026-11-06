#include "Game.h"


#include <iostream>

int main()
{
	Game* game = Game::getInstance();
	game->run();

	return 0;
}