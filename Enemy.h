#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

class Enemy {
private:
    sf::Texture texture;    
    float speed = 2.f; // Slightly slower than the player

public:
    std::optional<sf::Sprite> sprite;

public:
    
    void Initialize(sf::Vector2f startPosition);
    void Load();
    void Update(sf::Vector2f playerPosition); // Pass player position so enemy can chase!
    void Draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const {
        return sprite.has_value() ? sprite->getPosition() : sf::Vector2f(0.f, 0.f);
    }
};
