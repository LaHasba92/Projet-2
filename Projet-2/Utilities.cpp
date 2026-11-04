#include "Utilities.h"

Vector2::Vector2(int x, int y)
	: x(x), y(y)
{
}

int Vector2::getX() const
{
	return x;
}

int Vector2::getY() const
{
	return y;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

bool Vector2::operator==(const Vector2& other) const
{
	return x == other.x && y == other.y;
}