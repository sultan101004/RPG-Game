#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional> 
#include <vector>
#include <cmath>

using namespace sf;
using namespace std;

// 1. Group the bullet's visual component and physical velocity vector together
struct Bullet {
    sf::RectangleShape shape;
    sf::Vector2f direction;
};

// Fixed Vector Normalization parameters to avoid compiler pass-by-reference copies
sf::Vector2f NormalizeVector(const sf::Vector2f& source) {
    float m = sqrt(source.x * source.x + source.y * source.y);
    if (m != 0.f) {
        return sf::Vector2f(source.x / m, source.y / m);
    }
    return source;
}

int main()
{
    // -------------------------- INITIALIZE -------------------------------- //
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML 3 RPG Engine", sf::State::Windowed, settings);
    window.setFramerateLimit(60); // Essential so bullets move at a consistent speed!

    bool isMovingUp = false; bool isMovingDown = false;
    bool isMovingLeft = false; bool isMovingRight = false;

    // -------------------------- ASSET LOADING ----------------------------- //
    sf::Texture playerTexture;
    sf::Texture enemyTexture;
    std::optional<sf::Sprite> playerSprite;
    std::optional<sf::Sprite> enemySprite;

    std::vector<Bullet> bullets;
    float bulletSpeed = 5.f; // Pixels per frame at 60 FPS

    if (enemyTexture.loadFromFile("Assets/Skeleton/Textures/spritesheet.png")) {
        cout << "Enemy loaded successfully!" << endl;
        enemySprite.emplace(enemyTexture);
        enemySprite->setPosition(sf::Vector2f(400.f, 300.f));
        enemySprite->setTextureRect({ {0, 0}, {64, 64} });
        enemySprite->scale({ 2.0f, 2.0f });
    }

    if (playerTexture.loadFromFile("Assets/Player/Textures/spritesheet.png")) {
        cout << "Player loaded successfully!" << endl;
        playerSprite.emplace(playerTexture);
        playerSprite->setTextureRect({ {0, 0}, {64, 64} });
        playerSprite->scale({ 2.0f, 2.0f });
        playerSprite->setPosition(sf::Vector2f(100.f, 100.f));
    }

    // -------------------------- MAIN GAME LOOP ---------------------------- //
    while (window.isOpen())
    {
        // -------------------------- PROCESS EVENTS ------------------------ //
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                switch (keyPressed->code)
                {
                case sf::Keyboard::Key::W: case sf::Keyboard::Key::Up:    isMovingUp = true;    break;
                case sf::Keyboard::Key::S: case sf::Keyboard::Key::Down:  isMovingDown = true;  break;
                case sf::Keyboard::Key::A: case sf::Keyboard::Key::Left:  isMovingLeft = true;  break;
                case sf::Keyboard::Key::D: case sf::Keyboard::Key::Right: isMovingRight = true; break;

                    // FIXED: Single discrete instantiation actions on click
                case sf::Keyboard::Key::Space:
                    if (playerSprite.has_value() && enemySprite.has_value())
                    {
                        Bullet newBullet;
                        newBullet.shape.setSize(sf::Vector2f(15.f, 15.f)); // Square bullet configuration
                        newBullet.shape.setFillColor(sf::Color::Yellow);

                        // Spawn bullet right at the center of the player
                        newBullet.shape.setPosition(playerSprite->getPosition());

                        // Target calculation vector: Target minus Origin
                        sf::Vector2f targetDir = enemySprite->getPosition() - playerSprite->getPosition();
                        newBullet.direction = NormalizeVector(targetDir);

                        bullets.push_back(newBullet);
                    }
                    break;
                default: break;
                }
            }

            if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                switch (keyReleased->code)
                {
                case sf::Keyboard::Key::W: case sf::Keyboard::Key::Up:    isMovingUp = false;    break;
                case sf::Keyboard::Key::S: case sf::Keyboard::Key::Down:  isMovingDown = false;  break;
                case sf::Keyboard::Key::A: case sf::Keyboard::Key::Left:  isMovingLeft = false;  break;
                case sf::Keyboard::Key::D: case sf::Keyboard::Key::Right: isMovingRight = false; break;
                default: break;
                }
            }
        }

        // -------------------------- UPDATE LOGIC -------------------------- //
        if (playerSprite.has_value())
        {
            sf::Vector2f movement({ 0.f, 0.f });
            float speed = 4.f;

            if (isMovingUp)    movement.y -= speed;
            if (isMovingDown)  movement.y += speed;
            if (isMovingLeft)  movement.x -= speed;
            if (isMovingRight) movement.x += speed;

            playerSprite->move(movement);
        }

        // FIXED: Loop over active project array and alter tracking vectors smoothly
        for (size_t i = 0; i < bullets.size(); i++)
        {
            bullets[i].shape.move(bullets[i].direction * bulletSpeed);
        }

        // -------------------------- RENDERING STEP ------------------------ //
        window.clear(sf::Color::Black);

        if (playerSprite.has_value()) window.draw(*playerSprite);
        if (enemySprite.has_value())  window.draw(*enemySprite);

        // Render every single bullet present in flight tracking arrays
        for (const auto& b : bullets)
        {
            window.draw(b.shape);
        }

        window.display();
    }

    return 0;
}