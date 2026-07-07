#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional> 
#include <vector>
#include <cmath>
#include "Player.h"  // Bullet struct lives safely inside here
#include "Enemy.h" 
#include "Utility.h" 

using namespace sf;
using namespace std;

int main() {
    // -------------------------- INITIALIZE -------------------------------- //
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML 3 RPG Engine", sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    // -------------------------- ASSET LOADING ----------------------------- //
    std::vector<Bullet> bullets;
    float bulletSpeed = 5.f;

    // Instantiate and set up Player Entity
    Player player;
    player.Initialize();
    player.Load();

    // Instantiate and set up Enemy Entity
    Enemy enemy;
    enemy.Load();
    enemy.Initialize(sf::Vector2f(600.f, 400.f)); // Spawn enemy away from the player coordinator

    // Math tools instance for processing local vectors if needed
    Utility math;

    // -------------------------- MAIN GAME LOOP ---------------------------- //
    while (window.isOpen()) {

        // -------------------------- PROCESS EVENTS ------------------------ //
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            // Pass event data down with the singular enemy instance for processing
            player.HandleInput(*event, bullets, enemy);
        }

        // -------------------------- UPDATE LOGIC -------------------------- //
        player.Update();

        // Update enemy AI matrix and pass the player's tracking vector coordinates
        enemy.Update(player.getPosition());

        // Linear projectile movement transformations
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].shape.move(bullets[i].direction * bulletSpeed);
        }

        // -------------------------- RENDERING STEP ------------------------ //
        window.clear(sf::Color::Black);

        // Render game actors
        player.Draw(window);
        enemy.Draw(window);

        // Render project arrays
        for (const auto& b : bullets) {
            window.draw(b.shape);
        }

        window.display();
    }

    return 0;
}