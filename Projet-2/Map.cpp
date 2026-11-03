// Nathan BAURIN
#include "Map.h"
#include <iostream>

// Crée une carte avec les dimensions reçues dans le fichier Map.h. Si les dimensions sont invalides, la carte reste vide.
Map::Map(int mapWidth, int mapHeight)
// Initialise les attributs de la carte avant d'entrer dans le constructeur
    : width(mapWidth), height(mapHeight)
{
    // Vérifie que les dimensions permettent de créer une grille
    if (width > 0 && height > 0)
    {
        // Crée un tableau contenant une case par position de la carte
        // Les accolades initialisent toutes les cases à 0
        cells = new int[width * height] {};
    }
    else
    {
        // Si les dimensions sont incorrectes, la carte reste vide
        width = 0;
        height = 0;
    }

}

// Libère le tableau créé par new[] dans le constructeur
Map::~Map()
{
    delete[] cells;
}

// Convertit une position x/y en indice dans le tableau à une dimension
int Map::get1DCell(Vector2 position) const
{
    // Exemple avec une largeur de 20 et la position (3, 2) :
    // 2 * 20 + 3 donne l'indice 43
    return position.y * width + position.x;
}
// Charge les informations de la carteuj
void Map::display() const
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = y * width + x;
            std::cout << cells[index] << ' ';
        }



        std::cout << '\n';
    }
}