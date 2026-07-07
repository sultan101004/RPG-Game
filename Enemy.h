#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Enemy {
private:
    sf::Texture texture;
    float speed = 2.f; // Slightly slower tracking speed than the player

    sf::Vector2i size;
    sf::RectangleShape boundingBox; // For yellow outline debug collision tracking

public:
    std::optional<sf::Sprite> sprite;

public:
    void Initialize(sf::Vector2f startPosition);
    void Load();

    // Pass player position so the enemy AI can calculate its chase vector
    void Update(sf::Vector2f playerPosition);

    void Draw(sf::RenderWindow& window);

    // Coordinate state evaluation functions
    sf::Vector2f getPosition() const {
        return sprite.has_value() ? sprite->getPosition() : sf::Vector2f(0.f, 0.f);
    }

    sf::FloatRect getGlobalBounds() const {
        return sprite.has_value() ? sprite->getGlobalBounds() : sf::FloatRect();
    }
};