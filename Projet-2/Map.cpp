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

// Convertit une position en indice dans le tableau.
int Map::get1DCell(Vector2 position) const
{
    return position.getY() * width + position.getX();
}

// Vérifie si la position se trouve dans les limites de la carte.
bool Map::isInsideMap(Vector2 position) const
{
    int x = position.getX();
    int y = position.getY();

    return x >= 0 && x < width && y >= 0 && y < height;
}

// Change une case si sa position et son type sont valides.
bool Map::setCell(Vector2 position, E_CellType cellType)
{
    if (!isInsideMap(position))
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

// Associe un symbole et des propriétés à chaque terrain.
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

// Affiche le symbole associé à chaque case.
void Map::display() const
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Vector2 position(x, y);
            int index = get1DCell(position);
            int cellType = cells[index];

            std::cout << cellInfos[cellType].symbol << ' ';
        }

        std::cout << '\n';
    }
}

// Vérifie si la case peut être traversée à pied.
bool Map::isWalkable(Vector2 position) const
{
    if (!isInsideMap(position))
    {
        return false;
    }

    int index = get1DCell(position);
    int cellType = cells[index];

    return cellInfos[cellType].isWalkable;
}

// Vérifie si la case peut être traversée à la nage.
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