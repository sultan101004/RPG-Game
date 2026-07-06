#include "Enemy.h"
#include <iostream>
#include <cmath>

void Enemy::Initialize(sf::Vector2f startPosition) {
    // We pass a position so we can spawn enemies at different locations
    if (sprite.has_value()) {
        sprite->setPosition(startPosition);
    }
}

void Enemy::Load() {
    if (texture.loadFromFile("Assets/Skeleton/Textures/spritesheet.png")) {
        std::cout << "Enemy loaded successfully!" << std::endl;
        sprite.emplace(texture);
        sprite->setTextureRect({ {0, 0}, {64, 64} });
        sprite->scale({ 2.0f, 2.0f });
    }
}

void Enemy::Update(sf::Vector2f playerPosition) {
    if (sprite.has_value()) {
        // Simple AI: Calculate direction vector toward the player
        sf::Vector2f enemyPos = sprite->getPosition();
        sf::Vector2f direction = playerPosition - enemyPos;

        // Calculate distance
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance > 5.f) { // Prevents the enemy from jittering when it reaches the player
            // Normalize the direction vector
            sf::Vector2f normalizedDirection = direction / distance;

            // Move toward player
            sprite->move(normalizedDirection * speed);
        }
    }
}

void Enemy::Draw(sf::RenderWindow& window) {
    if (sprite.has_value()) {
        window.draw(*sprite);
    }
}