#pragma once

#include "Map.h"


class Game
{
public:
	static Game* getInstance();
	void run();

private:
	Game() = default;

	Map map{ 20, 10 };
};

