//Nathan Baurin

#pragma once

#include "Utilities.h"

#include <vector>

enum class E_CellType // sert a definir le type de cellule dans la map
{
	Ground,
	Water,
	Mountain,
	Exit,
	Count
};

class TileInfo // sert a definir les caracteristiques d'une cellule
{
public:
	char symbol = '.';
	bool isWalkable = true;
	bool isSwimmable = false;
};

class Map // sert a definir la map du jeu
{
public:
	Map(int width, int height); 
	~Map(); // Destructeur

	Map(const Map&) = delete;			  // Constructeur de copie supprimé
	Map& operator=(const Map&) = delete; // Opérateur d'affectation supprimé

	int get1Dcell(Vector2 position) const;    // retourne l'index de la cellule dans le tableau 1D
	bool loadFromFile(const char* filename); // charge la map depuis un fichier
	void display() const;					// affiche la map dans la console
	bool setCell(Vector2 position, E_CellType type); // modifie le type de cellule a la position donnee
private:
	int* cells = nullptr; // tableau 1D contenant les types de cellules
	int width = 0;			// largeur de la map
	int height = 0;		// hauteur de la map

	TileInfo tileInfos[
		static_cast<int>(E_CellType::Count)
	]{};			 // tableau contenant les caracteristiques de chaque type de cellule

		void initializeTileInfos(); // initialise le tableau tileInfos avec les caracteristiques de chaque type de cellule
