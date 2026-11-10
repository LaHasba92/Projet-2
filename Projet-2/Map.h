// Nathan Baurin
#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "Utilities.h"

// Types de cases de la carte.
enum E_CellType
{
    Ground = 0,
    Water,
    Mountain,
    Exit,
    CellType_Count
};

// Informations liées à un type de case.
struct CellInfo
{
    char symbol = '.';
    bool isWalkable = true;
    bool isSwimmable = false;
};

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
    bool isExit(Vector2 position) const;

    Vector2 getPlayerSpawn() const;
    const std::vector<Vector2>& getEnemySpawns() const;

    void display() const;
    void display(Vector2 playerPosition) const;
    void display(
        Vector2 playerPosition,
        const std::vector<Vector2>& enemyPositions
    ) const;

    bool loadFromFile(const char* fileName);

private:
    int* cells = nullptr;
    int width = 0;
    int height = 0;

    CellInfo cellInfos[CellType_Count]{};

    Vector2 playerSpawn{};
    std::vector<Vector2> enemySpawns{};

    void initializeCellInfos();
    bool isInsideMap(Vector2 position) const;
    bool isEnemyAt(
        Vector2 position,
        const std::vector<Vector2>& enemyPositions
    ) const;

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