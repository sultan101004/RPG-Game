// In Utility.h
#pragma once
#include <SFML/Graphics.hpp>

class Utility {
public:
    Utility();
    sf::Vector2f Normalize(const sf::Vector2f& v); // Added const
};