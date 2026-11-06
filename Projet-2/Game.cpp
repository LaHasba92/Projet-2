#include "Game.h"

#include <iostream>

Game* Game::getInstance()
{
	static Game game;
	return &game;
}

void Game::run()
{
	std::cout << "Bienvenue dans le jeu !\n";
	std::cout << "Chargement de la carte...\n";
	if (!map.loadFromFile("levels/level01.txt"))
	{
		std::cout << "Erreur lors du chargement de la carte.\n";
		return;
	}
	std::cout << "Carte chargec'est  avec succès !\n";
	map.display();
}