#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include "Utility.h"

// Forward declaration: Tell the compiler Enemy exists without including the whole file
class Enemy;

// Structure representing game projectiles
struct Bullet {
    sf::RectangleShape shape;
    sf::Vector2f direction;
};

class Player {
private:
    sf::Texture texture;

    // Movement system flags
    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;
    float speed = 4.f;

    // Shared utilities across player instances
    static Utility math;

    // Sprite layout configuration
    sf::Vector2i size;
    sf::RectangleShape boundingBox; // For green outline debug collision tracking

public:
    std::optional<sf::Sprite> sprite;

public:
    void Initialize();
    void Load();

    // Event interception and processing engine
    void HandleInput(const sf::Event& event, std::vector<Bullet>& gameBullets, const Enemy& enemy);

    void Update();
    void Draw(sf::RenderWindow& window);

    // Coordinate state evaluation functions
    sf::Vector2f getPosition() const {
        return sprite.has_value() ? sprite->getPosition() : sf::Vector2f(0.f, 0.f);
    }

    sf::FloatRect getGlobalBounds() const {
        return sprite.has_value() ? sprite->getGlobalBounds() : sf::FloatRect();
    }
};