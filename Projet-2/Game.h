// Nathan Baurin
#pragma once

#include <vector>

#include "Map.h"
#include "Zombie.h"

class Player;

class Game
{
public:
    static Game* getInstance();
    void run();

private:
    Game() = default;

    bool loadLevel();
    bool playCurrentLevel(int& playerHealth);

    std::vector<Vector2> getEnemyPositions() const;
    void displayCurrentState(const Player& player) const;
    void updateEnemies(Player& player);
    void resolveCollisions(Player& player);

    Map map{ 20, 10 };
    std::vector<Zombie> enemies{};
    int currentLevel = 1;

    static constexpr int MAX_LEVELS = 5;
};