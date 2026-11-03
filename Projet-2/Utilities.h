//code : Nathan BAURIN
#pragma once
class Utilities
{

};

// Regroupe les coordonnées d'une position sur la carte
class Vector2
{
public:
    // colonne
    int x = 0;

    // ligne
    int y = 0;
};
void operator+(Vector2& a, Vector2& b);
void operator-(Vector2& a, Vector2& b);
bool operator==(Vector2& a, Vector2& b);