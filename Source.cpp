#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional> 
#include <vector>
#include <cmath>
#include "Player.h"  // Bullet struct lives here safely
#include "Enemy.h" 
#include "Utility.h" // Fixed: Include the header, not the .cpp

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

    Player player;
    player.Initialize();
    player.Load();

    Enemy enemy;
    enemy.Load();
    enemy.Initialize(sf::Vector2f(600.f, 400.f));

    Utility math;

    // -------------------------- MAIN GAME LOOP ---------------------------- //
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            player.HandleInput(*event, bullets);
        }

        // -------------------------- UPDATE LOGIC -------------------------- //
        player.Update();
        enemy.Update(player.getPosition());

        // FIXED: Bullets move forward along their own set direction vectors
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].shape.move(bullets[i].direction * bulletSpeed);
        }

        // -------------------------- RENDERING STEP ------------------------ //
        window.clear(sf::Color::Black);

        player.Draw(window);
        enemy.Draw(window);

        for (const auto& b : bullets) {
            window.draw(b.shape);
        }

        window.display();
    }

    return 0;
}