// Nathan BAURIN
#include "Map.h"
#include <iostream>

// Constructeur de la classe Map20
Map::Map(int width, int height)
	: width(width), height(height)
{
	if (width > 0 && height > 0)
	{
		cells = new int[width * height]; // allocation dynamique du tableau 1D
	}
	else
	{
		width = 0;
		height = 0;
	}

	initializeTileInfos(); // initialisation du tableau tileInfos avec les caracteristiques de chaque type de cellule
}

Map::~Map()
{
	delete[] cells; // libération de la mémoire allouée pour le tableau 1D
}

void Map::initializeTileInfos() // initialise le tableau tileInfos avec les caracteristiques de chaque type de cellule
{
	int ground = static_cast<int>(E_CellType::Ground);
	tileInfos[ground].symbol = '.';
	tileInfos[ground].isWalkable = true;
	tileInfos[ground].isSwimmable = false;

	int water = static_cast<int>(E_CellType::Water);
	tileInfos[water].symbol = '~';
	tileInfos[water].isWalkable = false;
	tileInfos[water].isSwimmable = true;

	int mountain = static_cast<int>(E_CellType::Mountain);
	tileInfos[mountain].symbol = 'A';
	tileInfos[mountain].isWalkable = false;
	tileInfos[mountain].isSwimmable = false;

	int exit = static_cast<int>(E_CellType::Exit);
	tileInfos[exit].symbol = 'E';
	tileInfos[exit].isWalkable = true;
	tileInfos[exit].isSwimmable = false;
}


void Map::display() const
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			int index = y * width + x; // calcul de l'index dans le tableau 1D
			std::cout << cells[index] << ' ';
		}
		std::cout << '\n';
	}
}