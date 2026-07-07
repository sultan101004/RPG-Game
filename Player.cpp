#include "Player.h"
#include "Enemy.h"
#include "Utility.h"
#include <iostream>

// Static member definition (Only once at the top)
Utility Player::math;

void Player::Initialize() {
    isMovingUp = false;
    isMovingDown = false;
    isMovingLeft = false;
    isMovingRight = false;

    size = sf::Vector2i(64, 64);

    boundingBox.setFillColor(sf::Color::Transparent); // Transparent fill
    boundingBox.setOutlineColor(sf::Color::Green);     // Green outline for debugging
    boundingBox.setOutlineThickness(1.f);
    boundingBox.setSize(sf::Vector2f({ size.x * 1.0f, size.y * 1.0f }));
}

void Player::Load() {
    if (texture.loadFromFile("Assets/Player/Textures/spritesheet.png")) {
        std::cout << "Player loaded successfully!" << std::endl;
        sprite.emplace(texture);

        int XIndex = 0; // Column index in the spritesheet
        int YIndex = 0; // Row index in the spritesheet

        sprite->setTextureRect({ {XIndex * size.x, YIndex * size.y}, {size.x, size.y} });
        sprite->setPosition(sf::Vector2f(100.f, 100.f));

        sprite->scale({ 1.5f, 1.5f });
        boundingBox.setSize(sf::Vector2f({ size.x * sprite->getScale().x, size.y * sprite->getScale().y }));
    }
}

void Player::HandleInput(const sf::Event& event, std::vector<Bullet>& gameBullets, const Enemy& enemy) {
    // 1. Movement Key Presses
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        switch (keyPressed->code) {
        case sf::Keyboard::Key::W: case sf::Keyboard::Key::Up:    isMovingUp = true;    break;
        case sf::Keyboard::Key::S: case sf::Keyboard::Key::Down:  isMovingDown = true;  break;
        case sf::Keyboard::Key::A: case sf::Keyboard::Key::Left:  isMovingLeft = true;  break;
        case sf::Keyboard::Key::D: case sf::Keyboard::Key::Right: isMovingRight = true; break;

        case sf::Keyboard::Key::Space: {
            if (sprite.has_value()) {
                Bullet newBullet;
                newBullet.shape.setSize({ 15.f, 5.f });
                newBullet.shape.setFillColor(sf::Color::Yellow);

                // Center the bullet offset
                newBullet.shape.setPosition(sprite->getPosition() + sf::Vector2f(32.f, 32.f));

                sf::Vector2f baseDirection(1.f, 0.f);
                newBullet.direction = math.Normalize(baseDirection);

                gameBullets.push_back(newBullet);
            }
            break;
        }
        default: break;
        }
    }

    // 2. Movement Key Releases
    if (const auto* keyReleased = event.getIf<sf::Event::KeyReleased>()) {
        switch (keyReleased->code) {
        case sf::Keyboard::Key::W: case sf::Keyboard::Key::Up:    isMovingUp = false;    break;
        case sf::Keyboard::Key::S: case sf::Keyboard::Key::Down:  isMovingDown = false;  break;
        case sf::Keyboard::Key::A: case sf::Keyboard::Key::Left:  isMovingLeft = false;  break;
        case sf::Keyboard::Key::D: case sf::Keyboard::Key::Right: isMovingRight = false; break;
        default: break;
        }
    }

    // 3. Optional: Mouse Click Shooting
    if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mousePressed->button == sf::Mouse::Button::Left && sprite.has_value()) {
            Bullet newBullet;
            newBullet.shape.setSize({ 10.f, 10.f });
            newBullet.shape.setFillColor(sf::Color::Red);
            newBullet.shape.setPosition(sprite->getPosition() + sf::Vector2f(32.f, 32.f));
            newBullet.direction = sf::Vector2f(1.f, 0.f);

            gameBullets.push_back(newBullet);
        }
    }

    // Update debug bounding box position to match the sprite
    if (sprite.has_value()) {
        boundingBox.setPosition(sprite->getPosition());
    }

    // FIXED: Safely check for collision against the singular enemy reference
    if (sprite.has_value() && Utility::checkRectCollision(sprite->getGlobalBounds(), enemy.getGlobalBounds())) {
        std::cout << "Collision detected!" << std::endl;
    }
    else {
        std::cout << "No collision." << std::endl;
    }
}

void Player::Update() {
    if (sprite.has_value()) {
        sf::Vector2f movement({ 0.f, 0.f });

        if (isMovingUp)    movement.y -= speed;
        if (isMovingDown)  movement.y += speed;
        if (isMovingLeft)  movement.x -= speed;
        if (isMovingRight) movement.x += speed;

        sprite->move(movement);
    }
}

void Player::Draw(sf::RenderWindow& window) {
    if (sprite.has_value()) {
        window.draw(*sprite);
    }
    window.draw(boundingBox); // Draw the debug green bounding box outline
}