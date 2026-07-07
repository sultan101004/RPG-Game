#include "Enemy.h"
#include <iostream>
#include <cmath>

using namespace std;

void Enemy::Initialize(sf::Vector2f startPosition) {
    size = sf::Vector2i(64, 64);

	texture.loadFromFile("Assets/Skeleton/Textures/spritesheet.png");
    sprite.emplace(texture);
    // Render the default frame from the sprite sheet matrix
    sprite->setTextureRect({ {0, 0}, {size.x, size.y} });
    sprite->scale({ 2.0f, 2.0f });

    // Configure the debug bounding box visual properties
    boundingBox.setFillColor(sf::Color::Transparent); // Transparent fill
    boundingBox.setOutlineColor(sf::Color::Yellow);    // Yellow outline for enemies
    boundingBox.setOutlineThickness(1.f);
    boundingBox.setSize(sf::Vector2f({ size.x * 2.0f, size.y * 2.0f })); // Matches default scaling factor
    
    if (sprite.has_value()) {
        sprite->setPosition(startPosition);
    }
}

void Enemy::Load() {
    if (sprite.has_value()) {
        std::cout << "Enemy loaded successfully!" << std::endl;
       
       
        
        // Update the bounding box matching scaled sprite dimensions
        boundingBox.setSize(sf::Vector2f({ size.x * sprite->getScale().x, size.y * sprite->getScale().y }));
    }
}

void Enemy::Update(sf::Vector2f playerPosition) {
    if (sprite.has_value()) {
        // Simple AI Target Acquisition: Calculate direction vector toward the player
        sf::Vector2f enemyPos = sprite->getPosition();
        sf::Vector2f direction = playerPosition - enemyPos;

        // Evaluate distance magnitude
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance > 5.f) { // Dead-zone tolerance buffer limits sprite stutter loops
            // Normalize direction vector inline
            sf::Vector2f normalizedDirection = direction / distance;

            // Step translation towards objective coordinates
            sprite->move(normalizedDirection * speed);
        }

        // Anchor bounding box transformation vectors to tracking entity positions
        boundingBox.setPosition(sprite->getPosition());
    }
}

void Enemy::Draw(sf::RenderWindow& window) {
    if (sprite.has_value()) {
       // cout << "Enemy has value" << endl;
        window.draw(*sprite);
    }
    window.draw(boundingBox); // Draw the yellow layout box bounds boundary
}