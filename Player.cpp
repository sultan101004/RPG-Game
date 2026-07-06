#include "Player.h"

#include <iostream>

Utility Player::math;

void Player::Initialize() {
    isMovingUp = false;
    isMovingDown = false;
    isMovingLeft = false;
    isMovingRight = false;
}

void Player::Load() {
    if (texture.loadFromFile("Assets/Player/Textures/spritesheet.png")) {
        std::cout << "Player loaded successfully!" << std::endl;
        sprite.emplace(texture);
        sprite->setTextureRect({ {0, 0}, {64, 64} });
        sprite->scale({ 2.0f, 2.0f });
        sprite->setPosition(sf::Vector2f(100.f, 100.f));
    }
}

void Player::HandleInput(const sf::Event& event, std::vector<Bullet>& gameBullets) {
    // 1. Movement Key Presses
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        switch (keyPressed->code) {
        case sf::Keyboard::Key::W: case sf::Keyboard::Key::Up:    isMovingUp = true;    break;
        case sf::Keyboard::Key::S: case sf::Keyboard::Key::Down:  isMovingDown = true;  break;
        case sf::Keyboard::Key::A: case sf::Keyboard::Key::Left:  isMovingLeft = true;  break;
        case sf::Keyboard::Key::D: case sf::Keyboard::Key::Right: isMovingRight = true; break;

        // ... inside Player::HandleInput under case sf::Keyboard::Key::Space:
        case sf::Keyboard::Key::Space: {
            if (sprite.has_value()) {
                Bullet newBullet;
                newBullet.shape.setSize({ 15.f, 5.f });
                newBullet.shape.setFillColor(sf::Color::Yellow);

                newBullet.shape.setPosition(sprite->getPosition() + sf::Vector2f(32.f, 32.f));

                // FIXED: Give it a baseline direction vector before normalizing!
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

    // 3. Optional: Mouse Click Shooting (Shoots Right for now)
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
}


