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

    Vector2 operator+(const Vector2& b) const;
    Vector2 operator-(const Vector2& b) const;
    Vector2& operator+=(const Vector2& b);
    bool operator==(const Vector2& b) const;
};