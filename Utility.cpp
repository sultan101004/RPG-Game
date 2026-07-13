#include "Utility.h"
#include <cmath>

sf::Vector2f Utility::Normalize(const sf::Vector2f& v) {
    float len = std::sqrt(v.x * v.x + v.y * v.y);

    // Safety check to prevent dividing by zero (which creates invalid NaN values)
    return (len == 0.f) ? sf::Vector2f(0.f, 0.f) : sf::Vector2f(v.x / len, v.y / len);
}

bool Utility::checkRectCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
    // SFML 3 structural coordinate intersection evaluations (.position and .size)
    if (rect1.position.x < rect2.position.x + rect2.size.x &&
        rect1.position.x + rect1.size.x > rect2.position.x &&
        rect1.position.y < rect2.position.y + rect2.size.y &&
        rect1.position.y + rect1.size.y > rect2.position.y)
    {
        return true; // Overlap detected!
    }

    return false; // Bounds are clear.
}