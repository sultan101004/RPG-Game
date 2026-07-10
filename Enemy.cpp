#include "Enemy.h"
#include <iostream>
#include <cmath>

using namespace std;

Enemy::Enemy() : fpsText(font) {}

void Enemy::Initialize(sf::Vector2f startPosition) {
    size = sf::Vector2i(64, 64);
    health = 100;

	if (!texture.loadFromFile("Assets/Skeleton/Textures/spritesheet.png")) {
        std::cout << "Error: Could not load Skeleton texture!" << std::endl;
    }
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
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cout << "Error loading font!" << std::endl;
    }
    else {
        // Configure the member variable, don't create a local one!
        fpsText.setFont(font);
        fpsText.setCharacterSize(24);
        fpsText.setFillColor(sf::Color::Yellow);
        fpsText.setPosition(this->getPosition());
    }
}


void Enemy::Update(sf::Vector2f playerPosition,float dt) {

    float speed = 150.f; // Adjust speed based on delta time for frame-rate independence
    
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
            sprite->move(normalizedDirection * speed * dt);
        }

        fpsText.setString("Health: " + std::to_string(static_cast<int>(health)));
        
        boundingBox.setPosition(sprite->getPosition());
        fpsText.setPosition(this->getPosition());
    }
}

void Enemy::Draw(sf::RenderWindow& window) {
	if (health <= 0) {
		return; // Skip drawing if the enemy is dead
	}
    if (sprite.has_value()) {
       // cout << "Enemy has value" << endl;
        window.draw(*sprite);
    }
    window.draw(boundingBox); // Draw the yellow layout box bounds boundary
	window.draw(fpsText); // Draw the health text on top of the enemy sprite
}