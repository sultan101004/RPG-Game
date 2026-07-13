#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional> 
#include <vector>
#include <cmath>

#include "Player.h"  // Bullet struct lives safely inside here
#include "Enemy.h" 
#include "Utility.h" 
#include "Bullet.h"
#include "Map.h"

using namespace sf;
using namespace std;


int main() {
    // -------------------------- INITIALIZE -------------------------------- //
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML 3 RPG Engine", sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    // -------------------------- ASSET LOADING ----------------------------- //
   
   

    // FIXED: Load font safely using openFromFile, don't pass the string to the constructor twice
    sf::Font font;
    if (!font.openFromFile("Assets/Fonts/arial.ttf")) {
        std::cout << "Error loading font!" << std::endl;
    }

    // Declare and configure the text object ONCE outside the loop
    sf::Text fpsText(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::Yellow);
    fpsText.setPosition({ 10.f, 10.f });

    // Instantiate and set up Entities
    Player player;
    player.Initialize();
    player.Load();

    Enemy enemy;
    enemy.Load();
    enemy.Initialize(sf::Vector2f(600.f, 400.f));

    Map map;
    map.Load("Assets/Maps/Level1.map");

    sf::Clock clock;
    
    float fpsTimer = 0.f;
    int frameCount = 0;

    // -------------------------- MAIN GAME LOOP ---------------------------- //
    while (window.isOpen()) {

        // 1. Calculate Delta Time safely
        sf::Time deltaTimer = clock.restart();
        float deltaTime = deltaTimer.asSeconds();

        // 2. Calculate smooth FPS
        fpsTimer += deltaTime;
        frameCount++;

        if (fpsTimer >= 0.5f) {
            float fps = frameCount / fpsTimer;
            fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
            fpsTimer = 0.f;
            frameCount = 0;
        }

        // -------------------------- PROCESS EVENTS ------------------------ //
        // FIXED: Events are processed at the start of the frame loop step
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            player.HandleInput(*event, enemy);
        }

        // -------------------------- UPDATE LOGIC -------------------------- //
        // FIXED: Code only updates positions ONCE per frame loop iteration
        
        map.Update(deltaTime);
        player.Update(deltaTime);
        enemy.Update(player.getPosition(), deltaTime);


        // Projectile translation logic and boundary cleaner
        for (size_t i = 0; i < player.bullets.size(); ) {
            player.bullets[i].Update(deltaTime);

            if (enemy.getHealth() > 0) {

                // 1. Check for Collision with Enemy
                if (Utility::checkRectCollision(player.bullets[i].shape.getGlobalBounds(), enemy.getGlobalBounds())) {
                    player.bullets.erase(player.bullets.begin() + i);
                    std::cout << "Collision detected!" << std::endl;
                    enemy.reduceHealth(10); // Reduce enemy health by 10 on collision

                    continue; // IMPORTANT: Skip to the next iteration since we erased this bullet!
                }
            }
            // 2. Check if the bullet is out of the window bounds
            sf::Vector2f pos = player.bullets[i].shape.getPosition();
            if (pos.x < -50.f || pos.x > 850.f || pos.y < -50.f || pos.y > 650.f) {
                player.bullets.erase(player.bullets.begin() + i);
                continue; // IMPORTANT: Skip to the next iteration since we erased this bullet!
            }

            // 3. If the bullet survived both checks, move to the next one
            i++;
        }

        // -------------------------- RENDERING STEP ------------------------ //
        // FIXED: Only clear, draw, and display ONCE at the end of the loop frame
        window.clear(sf::Color::Black);

        map.Draw(window);
        // Render game actors
        player.Draw(window);
        enemy.Draw(window);

        // Render bullets array
        for (const auto& b : player.bullets) {
            window.draw(b.shape);
        }

        window.draw(fpsText); // Draw UI elements on top of game textures
        window.display();
    }

    return 0;
}