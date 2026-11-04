#include "Map.h"

#include <iostream>

// Crée la grille et initialise ses propriétés.
Map::Map(int mapWidth, int mapHeight)
    : width(mapWidth), height(mapHeight)
{
    if (width > 0 && height > 0)
    {
        cells = new int[width * height] {};
    }
    else
    {
        width = 0;
        height = 0;
    }

    initializeCellInfos();
}

// Libère le tableau créé par new[].
Map::~Map()
{
    delete[] cells;
}

// Configure l'affichage et les propriétés de chaque terrain.
void Map::initializeCellInfos()
{
    cellInfos[Ground].symbol = '.';
    cellInfos[Ground].isWalkable = true;
    cellInfos[Ground].isSwimmable = false;

    cellInfos[Water].symbol = '~';
    cellInfos[Water].isWalkable = false;
    cellInfos[Water].isSwimmable = true;

    cellInfos[Mountain].symbol = 'A';
    cellInfos[Mountain].isWalkable = false;
    cellInfos[Mountain].isSwimmable = false;

    cellInfos[Exit].symbol = 'E';
    cellInfos[Exit].isWalkable = true;
    cellInfos[Exit].isSwimmable = false;
}

// Convertit une position en indice dans cells.
int Map::get1DCell(Vector2 position) const
{
    return position.y * width + position.x;
}

// Modifie une case si sa position est dans la carte.
bool Map::setCell(Vector2 position, E_CellType cellType)
{
    if (position.x < 0 || position.x >= width ||
        position.y < 0 || position.y >= height)
    {
        return false;
    }

    int type = static_cast<int>(cellType);

    if (type < Ground || type >= CellType_Count)
    {
        return false;
    }

    cells[get1DCell(position)] = type;
    return true;
}

// Affiche le symbole associé à chaque case.
void Map::display() const
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = y * width + x;
            int type = cells[index];
            std::cout << cellInfos[type].symbol << ' ';
        }

        std::cout << '\n';
    }
}  

// Vérifie si la position est à l'intérieur de la carte.
bool Map::isInsideMap(Vector2 position) const
{
	return position.x >= 0 && position.x < width &&
		position.y >= 0 && position.y < height;
}

// Vérifie si la case à la position donnée est praticable.
bool Map::isWalkable(Vector2 position) const
{
	if (!isInsideMap(position))
	{
		return false;
	}

	int index = get1DCell(position);
	int cellType = cells[index];

	return cellInfos[type].isWalkable;
}

// Vérifie si la case à la position donnée est nageable.
bool Map::isSwimmable(Vector2 position) const
{
	if (!isInsideMap(position))
	{
		return false;
	}
	int index = get1DCell(position);
	int cellType = cells[index];

	return cellInfos[cellType].isSwimmable;
}