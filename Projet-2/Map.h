#pragma once

#include "Utilities.h"

#include <vector>

#include <fstream>

#include <string>

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
	bool loadFromFile(const char* fileName);

private:
    int* cells = nullptr;
    int width = 0;
    int height = 0;

    // Chaque indice correspond à un élément de E_CellType.
    CellInfo cellInfos[CellType_Count]{};

    Vector2 playerSpawn;
    std::vector<Vector2> enemySpawns;
	void initializeCellInfos();
	bool isInsideMap(Vector2 position) const;

	void resetCells();

    bool readRow(
        std::ifstream& file,
        int y,
        int& heroCount,
        int& exitCount
      );
    
    bool loadRow(
        const std::string& line,
        int y,
        int& heroCount,
        int& exitCount
    );

	bool loadCell(
		char symbol,
		Vector2 position,
		int& heroCount,
		int& exitCount
	);
};