#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

struct Tile {
    int id;
    //sf::Texture* texture = nullptr;
    sf::Vector2i position;
};
