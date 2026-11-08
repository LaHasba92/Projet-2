#pragma once
#include "Utilities.h"

#include <vector>

// Types de cases repris du code du professeur.
enum E_CellType
{
    Ground = 0,
    Water,
    Mountain,
    Exit,
    CellType_Count
};

// Propriétés associées à un type de case.
struct CellInfo
{
    char symbol = '.';
    bool isWalkable = true;
    bool isSwimmable = false;
};

// La classe Map gère la grille et ses informations.
class Map
{
public:
    Map(int width, int height);
    ~Map();

    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    int get1DCell(Vector2 position) const;
    bool setCell(Vector2 position, E_CellType cellType);
	bool isWalkable(Vector2 position) const;
	bool isSwimmable(Vector2 position) const;
    void display() const;
    

private:
    int* cells = nullptr;
    int width = 0;
    int height = 0;

    // Chaque indice correspond à un élément de E_CellType.
    CellInfo cellInfos[CellType_Count]{};

    Vector2 playerSpawn{};
    std::vector<Vector2> enemySpawns{};
	void initializeCellInfos();
	bool isInsideMap(Vector2 position) const;
};