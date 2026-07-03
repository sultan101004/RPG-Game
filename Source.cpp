#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional> // Required for SFML 3 events and optional sprite initialization

using namespace sf;
using namespace std;

int main()
{
    // -------------------------- INITIALIZE -------------------------------- //

    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8; // Set the desired anti-aliasing level

    // SFML 3 Window Creation
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML 3 RPG Engine", sf::State::Windowed, settings);

    // window.setFramerateLimit(60);

    // State flags to completely eliminate the Windows operating system typing delay
    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;

    // -------------------------- ASSET LOADING ----------------------------- //

    sf::Texture playerTexture;
    std::optional<sf::Sprite> playerSprite;

    // Properly check if the file loads successfully before setting up our sprite
    if (playerTexture.loadFromFile("Assets/Player/Textures/spritesheet.png"))
    {
        cout << "Player loaded successfully!" << endl;

        // Initialize the sprite container inline now that the texture is ready
        playerSprite.emplace(playerTexture);

        int xIndex = 0; // Column index (0 to 6)
        int yIndex = 0; // Row index (0 to 3)

        // Crop out the single 64x64 frame utilizing the modern SFML 3 braced syntax
        playerSprite->setTextureRect({ {xIndex * 64, yIndex * 64}, {64, 64} });

        // Scale up the sprite coordinates to double its visual footprint
        playerSprite->scale({ 2.0f, 2.0f });
    }
    else
    {
        cout << "Failed to load player texture! Make sure the file exists in Assets/Player/Textures/spritesheet.png" << endl;
    }

    // -------------------------- MAIN GAME LOOP ---------------------------- //
    while (window.isOpen())
    {
        // -------------------------- PROCESS EVENTS ------------------------ //
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // SWITCH 1: Captures key down actions -> Activates velocity flags
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                switch (keyPressed->code)
                {
                case sf::Keyboard::Key::W:    case sf::Keyboard::Key::Up:    isMovingUp = true;    break;
                case sf::Keyboard::Key::S:    case sf::Keyboard::Key::Down:  isMovingDown = true;  break;
                case sf::Keyboard::Key::A:    case sf::Keyboard::Key::Left:  isMovingLeft = true;  break;
                case sf::Keyboard::Key::D:    case sf::Keyboard::Key::Right: isMovingRight = true; break;
                default: break;
                }
            }

            // SWITCH 2: Captures key up actions -> Deactivates velocity flags
            if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
            {
                switch (keyReleased->code)
                {
                case sf::Keyboard::Key::W:    case sf::Keyboard::Key::Up:    isMovingUp = false;    break;
                case sf::Keyboard::Key::S:    case sf::Keyboard::Key::Down:  isMovingDown = false;  break;
                case sf::Keyboard::Key::A:    case sf::Keyboard::Key::Left:  isMovingLeft = false;  break;
                case sf::Keyboard::Key::D:    case sf::Keyboard::Key::Right: isMovingRight = false; break;
                default: break;
                }
            }
        }

        // -------------------------- UPDATE LOGIC -------------------------- //
        // Processes state changes smoothly every single frame without stuttering
        if (playerSprite.has_value())
        {
            sf::Vector2f movement({ 0.f, 0.f });
            float speed = 0.5f; // Glides perfectly and smoothly at this frame pace

            if (isMovingUp)    movement.y -= speed;
            if (isMovingDown)  movement.y += speed;
            if (isMovingLeft)  movement.x -= speed;
            if (isMovingRight) movement.x += speed;

            playerSprite->move(movement);
        }

        // -------------------------- RENDERING STEP ------------------------ //
        window.clear(sf::Color::Black);

        // Safely unpack and draw our entity if valid
        if (playerSprite.has_value())
        {
            window.draw(*playerSprite);
        }

        window.display();
    }

    return 0;
}