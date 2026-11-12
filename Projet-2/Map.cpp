// Nathan Baurin
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

// Vérifie si une position est dans les limites de la carte.
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
    cellInfos[Ground] = { '.', true, false };
    cellInfos[Water] = { '~', false, true };
    cellInfos[Mountain] = { 'A', false, false };
    cellInfos[Exit] = { 'E', true, false };
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

// Vérifie si la case est de l'eau.
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

// Vérifie si la position correspond à la sortie.
bool Map::isExit(Vector2 position) const
{
    if (!isInsideMap(position))
    {
        return false;
    }

    int index = get1DCell(position);
    return cells[index] == Exit;
}

// Renvoie la position de départ du joueur.
Vector2 Map::getPlayerSpawn() const
{
    return playerSpawn;
}

// Renvoie les positions de départ des ennemis.
const std::vector<Vector2>& Map::getEnemySpawns() const
{
    return enemySpawns;
}

// Affiche uniquement les cases de la carte.
void Map::display() const
{
    display(Vector2(-1, -1));
}

// Affiche la carte avec le joueur.
void Map::display(Vector2 playerPosition) const
{
    const std::vector<Vector2> noEnemies;
    display(playerPosition, noEnemies);
}

// Affiche la carte avec le joueur et les ennemis.
void Map::display(
    Vector2 playerPosition,
    const std::vector<Vector2>& enemyPositions
) const
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Vector2 position(x, y);

            if (position == playerPosition)
            {
                std::cout << 'H' << ' ';
            }
            else if (isEnemyAt(position, enemyPositions))
            {
                std::cout << 'X' << ' ';
            }
            else
            {
                int index = get1DCell(position);
                int cellType = cells[index];

                std::cout << cellInfos[cellType].symbol << ' ';
            }
        }

        std::cout << '\n';
    }
}

// Vérifie si un ennemi se trouve sur la position.
bool Map::isEnemyAt(
    Vector2 position,
    const std::vector<Vector2>& enemyPositions
) const
{
    for (const Vector2& enemyPosition : enemyPositions)
    {
        if (position == enemyPosition)
        {
            return true;
        }
    }

    return false;
}

// Remet la carte à son état initial avant un nouveau chargement.
void Map::resetCells()
{
    enemySpawns.clear();
    playerSpawn = Vector2();

    for (int i = 0; i < width * height; ++i)
    {
        cells[i] = Ground;
    }
}

// Charge les lignes du fichier de niveau.
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
    std::string line;

    if (!std::getline(file, line))
    {
        return false;
    }

    if (!line.empty() && line.back() == '\r')
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

// Convertit un symbole du fichier en case ou position de départ.
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