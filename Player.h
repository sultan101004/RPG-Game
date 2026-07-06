#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include "Enemy.h"
#include "Utility.h"

// Define Bullet here so Player.h knows what a Vector of Bullets is
struct Bullet {
    sf::RectangleShape shape;
    sf::Vector2f direction;
};

class Player {
private:
    sf::Texture texture;

    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;
    float speed = 4.f;
    static Utility math;

public:
    std::optional<sf::Sprite> sprite;

public:
    void Initialize();
    void Load();

	//sf::Vector2f GetPosition();
    // Updated to accept the bullets vector from main
    void HandleInput(const sf::Event& event, std::vector<Bullet>& gameBullets);

    void Update();
    void Draw(sf::RenderWindow& window);
    // Add this inside the public section of Player.h
    sf::Vector2f getPosition() const {
        return sprite.has_value() ? sprite->getPosition() : sf::Vector2f(0.f, 0.f);
    }
};
