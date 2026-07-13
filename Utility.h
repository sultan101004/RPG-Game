#pragma once
#include <SFML/Graphics.hpp>

class Utility {
public:
    // Reduces a vector to a length of 1 while maintaining its heading
    static sf::Vector2f Normalize(const sf::Vector2f& v);

    // Evaluates static Axis-Aligned Bounding Box (AABB) intersection states
    static bool checkRectCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
};