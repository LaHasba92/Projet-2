#pragma once


class Vector2
{
public:
    Vector2(int x = 0, int y = 0);

    int getX() const;
    int getY() const;

    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    Vector2& operator+=(const Vector2& other);
    bool operator==(const Vector2& other) const;

private:
    int x = 0;
    int y = 0;
};