#include "Game.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include "Player.h"

// Renvoie l'unique instance de Game.
Game* Game::getInstance()
{
    static Game game;
    return &game;
}

// Charge la carte et crée un Zombie à chaque position X.
bool Game::loadLevel()
{
    std::string fileName =
        "levels/level0" + std::to_string(currentLevel) + ".txt";

    if (!map.loadFromFile(fileName.c_str()))
    {
        std::cout << "Impossible de charger " << fileName << ".\n";
        return false;
    }

    enemies.clear();

    for (const Vector2& spawn : map.getEnemySpawns())
    {
        enemies.emplace_back(spawn);
    }

    return true;
}

// Récupère les positions des zombies encore vivants.
std::vector<Vector2> Game::getEnemyPositions() const
{
    std::vector<Vector2> positions;

    for (const Zombie& enemy : enemies)
    {
        if (enemy.isAlive())
        {
            positions.push_back(enemy.getPosition());
        }
    }

    return positions;
}

// Efface l'écran et affiche la situation actuelle.
void Game::displayCurrentState(const Player& player) const
{
    std::system("cls");
    map.display(player.getPosition(), getEnemyPositions());

    std::cout << "Niveau : " << currentLevel << '\n';
    std::cout << "Points de vie : " << player.getHealth() << '\n';
}

// Fait jouer chaque Zombie vivant.
void Game::updateEnemies(Player& player)
{
    for (Zombie& enemy : enemies)
    {
        if (enemy.isAlive())
        {
            enemy.onUpdate(map, &player);
        }
    }
}

// Déclenche les réactions du joueur et du Zombie en collision.
void Game::resolveCollisions(Player& player)
{
    for (Zombie& enemy : enemies)
    {
        if (!enemy.isAlive() ||
            !(enemy.getPosition() == player.getPosition()))
        {
            continue;
        }

        player.onCollision(&enemy);

        if (enemy.isAlive())
        {
            enemy.onCollision(&player);
        }
    }
}

// Gère les tours jusqu'à la sortie ou la mort du joueur.
bool Game::playCurrentLevel(int& playerHealth)
{
    Player player(map.getPlayerSpawn(), playerHealth);

    while (player.isAlive() && !map.isExit(player.getPosition()))
    {
        displayCurrentState(player);
        player.readPlayerInputs(map);
        resolveCollisions(player);

        if (!player.isAlive() || map.isExit(player.getPosition()))
        {
            break;
        }

        updateEnemies(player);
        resolveCollisions(player);
    }

    displayCurrentState(player);
    playerHealth = player.getHealth();

    return player.isAlive();
}

// Enchaîne les niveaux tant que le joueur reste vivant.
void Game::run()
{
    int playerHealth = 3;

    while (currentLevel <= MAX_LEVELS)
    {
        if (!loadLevel())
        {
            return;
        }

        if (!playCurrentLevel(playerHealth))
        {
            std::cout << "Partie terminee.\n";
            return;
        }

        std::cout << "Niveau " << currentLevel << " termine !\n";
        ++currentLevel;
    }

    std::cout << "Tu as termine tous les niveaux !\n";
}