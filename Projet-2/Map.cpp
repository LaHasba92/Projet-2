#include "Map.h"

#include <iostream>

#include <fstream>

#include <string>

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

// Remet la carte à son état de départ.
void Map::resetCells()
{
    enemySpawns.clear();
    playerSpawn = Vector2();

    for (int i = 0; i < width * height; ++i)
    {
        cells[i] = Ground;
    }
}

// Charge toutes les lignes d'un fichier de niveau.
bool Map::loadFromFile(const char* fileName)
{
    std::ifstream file(fileName);

    if (!file.is_open())
    {
        return false;
    }

    resetCells();

    int heroCount = 0;
    int exitCount = 0;

    for (int y = 0; y < height; ++y)
    {
        if (!readRow(file, y, heroCount, exitCount))
        {
            return false;
        }
    }

    std::string extraLine;

    if (std::getline(file, extraLine))
    {
        return false;
    }

    return heroCount == 1 && exitCount == 1;
}

// Lit une ligne et retire le caractère CR des fins de ligne Windows.
bool Map::readRow(
    std::ifstream& file,
    int y,
    int& heroCount,
    int& exitCount
)
{
	std::string line;                // Variable pour stocker la ligne lue

	if (!std::getline(file, line))  // Lit une ligne du fichier et vérifie si la lecture a réussi
    {
        return false;
    }

	if (!line.empty() && line.back() == '\r') // Vérifie si le dernier caractère est un retour chariot (CR)
    {
        line.pop_back();                      
    }

    return loadRow(line, y, heroCount, exitCount);
}

// Vérifie la longueur de la ligne et lit chacune de ses cases.
bool Map::loadRow(
    const std::string& line,
    int y,
    int& heroCount,
    int& exitCount
)
{
    if (line.size() != static_cast<std::size_t>(width))
    {
        return false;
    }

    for (int x = 0; x < width; ++x)
    {
        Vector2 position(x, y);

        if (!loadCell(line[x], position, heroCount, exitCount))
        {
            return false;
        }
    }

    return true;
}

// Convertit le symbole du fichier en case et en position de départ.
bool Map::loadCell(
    char symbol,
    Vector2 position,
    int& heroCount,
    int& exitCount
)
{
    switch (symbol)
    {
    case '.':
        return setCell(position, Ground);
    case '~':
        return setCell(position, Water);
    case 'A':
        return setCell(position, Mountain);
    case 'E':
        ++exitCount;
        return setCell(position, Exit);
    case 'H':
        ++heroCount;
        playerSpawn = position;
        return setCell(position, Ground);
    case 'X':
        enemySpawns.push_back(position);
        return setCell(position, Ground);
    default:
        return false;
    }
}