#include "Utilities.h"

Vector2 Vector2::operator+(const Vector2& b) const {
    return { x + b.x, y + b.y };
}

Vector2 Vector2::operator-(const Vector2& b) const {
    return { x - b.x, y - b.y };
}

Vector2& Vector2::operator+=(const Vector2& b) {
    x += b.x;
    y += b.y;
    return *this;
}

bool Vector2::operator==(const Vector2& b) const {
    return x == b.x && y == b.y;
}