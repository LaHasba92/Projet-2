// Nathan BAURIN
#pragma once

#include "Utilities.h"

#include <vector>

// Liste des différents types de cases que la carte peut contenir.
enum class E_CellType
{
    Ground,   // Sol
    Water,    // Eau
    Mountain, // Montagne
    Exit,     // Sortie
    Count     // Nombre de types de cases, utilisé pour dimensionner tileInfos
};

// Regroupe les informations qui décrivent un type de case.
class TileInfo
{
public:
    char symbol = '.';             // Caractère affiché pour représenter la case
    bool isWalkable = true;        // Indique si un personnage peut marcher dessus
    bool isSwimmable = false;      // Indique si la case est de l'eau


};


// represente une carte de jeu composée de cases.
class Map
{
public:
    // Crée une carte de la largeur et de la hauteur indiquées.
    Map(int width, int height);

    // Libère la mémoire réservée pour les cases de la carte.
    ~Map();

    // Interdit la copie et l'affectation d'une carte.
    Map(const Map&) = delete;
    Map& operator=(const Map&) = delete;

    // Transforme une position x/y en indice dans le tableau à une dimension.
    int get1DCell(Vector2 position) const;

    // Charge les informations de la carte depuis un fichier texte.
    bool loadFromFile(const char* fileName);

    // permet d'afficher les valeurs des cases de la carte
    void display()const;

private:
    int* cells = nullptr; // Tableau dynamique qui contient les cases
    int width = 0;        // Nombre de colonnes de la carte
    int height = 0;       // Nombre de lignes de la carte

    // Associe des propriétés à chaque type de case de E_CellType.
    TileInfo tileInfos[
        static_cast<int>(E_CellType::Count)
    ]{};

        Vector2 playerSpawn{}; // Position de départ du joueur

        // Positions de départ des ennemis.
        std::vector<Vector2> enemySpawns{};
};