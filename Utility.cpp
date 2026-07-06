// In Utility.cpp
#include "Utility.h"
#include <cmath>

Utility::Utility() {}

sf::Vector2f Utility::Normalize(const sf::Vector2f& v) { // Added const
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    return (len == 0.f) ? sf::Vector2f(0.f, 0.f) : sf::Vector2f(v.x / len, v.y / len);
}