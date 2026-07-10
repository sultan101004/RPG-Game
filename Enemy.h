#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Enemy {
private:
    sf::Texture texture;
    float speed = 2.f; // Slightly slower tracking speed than the player
    int health;

    // Fonts
    sf::Font font;
    sf::Text fpsText;

	// Shared utilities across enemy instances
    sf::Vector2i size;
    sf::RectangleShape boundingBox; // For yellow outline debug collision tracking

public:
    std::optional<sf::Sprite> sprite;

public:
    Enemy();
    void Initialize(sf::Vector2f startPosition);
    void Load();
    void setHealth(int newHealth) { health = newHealth; }
    int getHealth() const { return health; }
    void reduceHealth(int amount) { health -= amount; if (health < 0) health = 0; }
    

    // Pass player position so the enemy AI can calculate its chase vector
    void Update(sf::Vector2f playerPosition, float dt);

    void Draw(sf::RenderWindow& window);

    // Coordinate state evaluation functions
    sf::Vector2f getPosition() const {
        return sprite.has_value() ? sprite->getPosition() : sf::Vector2f(0.f, 0.f);
    }

    sf::FloatRect getGlobalBounds() const {
        return sprite.has_value() ? sprite->getGlobalBounds() : sf::FloatRect();
    }
};