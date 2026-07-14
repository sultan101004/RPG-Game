#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional> 
#include <vector>
#include <cmath>

#include "Grid.h"
#include "MouseTile.h"

//#include "Player.h"  // Bullet struct lives safely inside here
//#include "Enemy.h" 
//#include "Utility.h" 
//#include "Bullet.h"
//#include "Map.h"

using namespace sf;
using namespace std;


int main() {
    // -------------------------- INITIALIZE -------------------------------- //
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Map Editor Engine", sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    Grid grid(sf::Vector2f({ 0,0 }), // position
              sf::Vector2i({ 16, 16}), // cellSize
              sf::Vector2i({ 10, 5}), // x, y
              sf::Vector2i({ 5, 5 }),  // scale 
                  Color::Green,        // color
                             2);       // thickness

    MouseTile mouseTile(sf::Vector2i({16,16}), sf::Vector2i({5,5}));

    grid.Initialize();
    mouseTile.Initialize();
    // -------------------------- ASSET LOADING ----------------------------- //
    grid.Load();
    mouseTile.Load();
    sf::Clock clock;
    //
    //float fpsTimer = 0.f;
    //int frameCount = 0;

    // -------------------------- MAIN GAME LOOP ---------------------------- //
    while (window.isOpen()) {

        // 1. Calculate Delta Time safely
        sf::Time deltaTimer = clock.restart();
        float deltaTime = deltaTimer.asSeconds();

        // -------------------------- PROCESS EVENTS ------------------------ //
        // FIXED: Events are processed at the start of the frame loop step
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            //player.HandleInput(*event, enemy);
        }
        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
        grid.Update(deltaTime);
        mouseTile.Update(deltaTime, mousePosition);
        // -------------------------- RENDERING STEP ------------------------ //
        // FIXED: Only clear, draw, and display ONCE at the end of the loop frame
        window.clear(sf::Color::Black);
        grid.Draw(window);
        mouseTile.Draw(window);
        window.display();
    }

    cout << "i just finished off!" << endl;

    return 0;
}