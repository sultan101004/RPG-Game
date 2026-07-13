#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>

#include "Utility.h"
#include"Bullet.h"

// Forward declaration: Tell the compiler Enemy exists without including the whole file
class Enemy;
class Bullet;

class Player {
private:
    sf::Texture texture;
    int health;

    // Movement system flags
    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;
    float speed = 4.f;

    // Fire rate management
    float fireRateTimer = 0.f;
    float maxFireRate = 0.150f; // 0.15 seconds between shots

    // Sprite layout configuration
    sf::Vector2i size;
    sf::RectangleShape boundingBox; // For green outline debug collision tracking

public:
    std::optional<sf::Sprite> sprite;
    std::vector<Bullet> bullets; // Store bullets fired by the player

public:
    void Initialize();
    void Load();
	void setHealth(int newHealth) { health = newHealth; }
	int getHealth() const { return health; }
	void reduceHealth(int amount) { health -= amount; if (health < 0) health = 0; }

    // Event interception and processing engine
    void HandleInput(const sf::Event& event, const Enemy& enemy);

    void Update(float dt);
    void Draw(sf::RenderWindow& window);

    // Coordinate state evaluation functions
    sf::Vector2f getPosition() const {
        return sprite.has_value() ? sprite->getPosition() : sf::Vector2f(0.f, 0.f);
    }

    sf::FloatRect getGlobalBounds() const {
        return sprite.has_value() ? sprite->getGlobalBounds() : sf::FloatRect();
    }
	sf::Vector2f getBullets() const {
		if (!bullets.empty()) {
			return bullets.back().shape.getPosition();
		}
		return sf::Vector2f(0.f, 0.f);
	}
};