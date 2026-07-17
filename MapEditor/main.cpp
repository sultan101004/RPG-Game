#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional> 
#include <vector>
#include <cmath>

#include "Grid.h"
#include "MouseTile.h"
#include "Mep.h"
#include "Panel.h"
#include "MapSaver.h"
#include "MapData.h"

//#include "Player.h"  // Bullet struct lives safely inside here
//#include "Enemy.h" 
//#include "Utility.h" 
//#include "Bullet.h"
//#include "Map.h"

using namespace sf;
using namespace std;
using namespace GUI;


int main() {
    // -------------------------- INITIALIZE -------------------------------- //
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Map Editor Engine", sf::State::Windowed, settings);
    window.setFramerateLimit(60);

    Grid grid(sf::Vector2f({ 100,50 }),   // position
              sf::Vector2i({ 16, 16}), // cellSize
              sf::Vector2i({ 10, 5}),  // x, y
              sf::Vector2i({ 4, 4 }),  // scale 
                  Color::Green,        // color
                             2);       // thickness

    MouseTile mouseTile(sf::Vector2i({16,16}), sf::Vector2i({4,4}), sf::Vector2f({100, 50}));
    Mep map(10, 5);

    grid.Initialize();
    mouseTile.Initialize();
    // -------------------------- ASSET LOADING ----------------------------- //
    grid.Load();
    mouseTile.Load();

    // -- SETUP MAP CONFIG (used when saving) --
    MapData mapConfig;
    mapConfig.version    = 1.0f;
    mapConfig.tilesheet  = "../Assets/World/Prison/tilesheet.png";
    mapConfig.name       = "Level 1";
    mapConfig.tileWidth  = 16;
    mapConfig.tileHeight = 16;
    mapConfig.scaleX     = 4;
    mapConfig.scaleY     = 4;
    mapConfig.mapWidth   = map.GetWidth();
    mapConfig.mapHeight  = map.GetHeight();

    // -- LOAD FONT & SETUP GUI --
    sf::Font font;
    if (!font.openFromFile("../Assets/Fonts/arial.ttf")) {
        std::cout << "ERROR: Could not load arial.ttf!" << std::endl;
    }

    sf::Texture btnTexture;
    if (!btnTexture.loadFromFile("../Assets/GUI/buttons.png")) {
        std::cout << "ERROR: Could not load buttons.png!" << std::endl;
    }

    // Create a 200px wide sidebar on the right side of the 800x600 window
    GUI::Panel sidebar(sf::Vector2f(600, 0), sf::Vector2f(200, 600));

    // Button 1: Toggle Layer
    sidebar.AddButton(std::make_unique<GUI::Button>(
        sf::Vector2f(620, 20), sf::Vector2f(160, 40), btnTexture, "Toggle Layer", font,
        [&mouseTile]() {
            mouseTile.ToggleLayer();
        }
    ));

    // Button 2: Save Map
    sidebar.AddButton(std::make_unique<GUI::Button>(
        sf::Vector2f(620, 70), sf::Vector2f(160, 40), btnTexture, "Save Map", font,
        [&map, &mapConfig]() {
            MapSaver::Save("../Assets/Maps/Level1.map", map.GetBgData(), mapConfig);
        }
    ));

    sf::Clock clock;

    // -------------------------- MAIN GAME LOOP ---------------------------- //
    while (window.isOpen()) {

        // 1. Calculate Delta Time safely
        sf::Time deltaTimer = clock.restart();
        float deltaTime = deltaTimer.asSeconds();

        // -------------------------- PROCESS EVENTS ------------------------ //
        // FIXED: Events are processed at the start of the frame loop step
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseEvent->button == sf::Mouse::Button::Left) {
                    // Convert screen pixels to world coordinates to fix any offset issues!
                    sf::Vector2i pixelPos(mouseEvent->position.x, mouseEvent->position.y);
                    sf::Vector2f clickPos = window.mapPixelToCoords(pixelPos);
                    
                    // 1. Give the GUI the first chance to consume the click!
                    if (sidebar.HandleClick(clickPos)) {
                        continue; // Click was inside the UI! Stop processing this click for the map.
                    }

                    // 2. If the GUI didn't consume it, allow the map editor to process it.
                    int index = mouseTile.HandleClick(clickPos);
                    if (index != -1) {
                        const sf::Sprite* previewSprite = mouseTile.GetTile();
                        if (previewSprite) {
                            // Pass the tile ID so Mep can remember what was placed for saving!
                            map.PlaceTile(index, mouseTile.GetActiveLayer(), *previewSprite, mouseTile.GetTileID());
                        }
                    }
                }
            }
            
            // DEMO: Mouse Wheel to scroll X axis
            if (const auto* scrollEvent = event->getIf<sf::Event::MouseWheelScrolled>()) {
                if (scrollEvent->wheel == sf::Mouse::Wheel::Vertical) {
                    if (scrollEvent->delta > 0) mouseTile.ChangeTile(1, 0); // Scroll Up = Next
                    else if (scrollEvent->delta < 0) mouseTile.ChangeTile(-1, 0); // Scroll Down = Previous
                }
            }

            // DEMO: Arrow Keys to move X and Y axis manually
            if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                if (keyEvent->scancode == sf::Keyboard::Scancode::L) mouseTile.ToggleLayer();
                else if (keyEvent->scancode == sf::Keyboard::Scancode::Up) mouseTile.ChangeTile(0, -1);
                else if (keyEvent->scancode == sf::Keyboard::Scancode::Down) mouseTile.ChangeTile(0, 1);
                else if (keyEvent->scancode == sf::Keyboard::Scancode::Left) mouseTile.ChangeTile(-1, 0);
                else if (keyEvent->scancode == sf::Keyboard::Scancode::Right) mouseTile.ChangeTile(1, 0);
            }
        }
        
        // Convert screen pixels to world coordinates to fix hover offset issues!
        sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        
        // Update components
        sidebar.Update(mousePosition); // Update GUI hover states
        grid.Update(deltaTime);
        mouseTile.Update(deltaTime, mousePosition);
        // -------------------------- RENDERING STEP ------------------------ //
        // FIXED: Only clear, draw, and display ONCE at the end of the loop frame
        window.clear(sf::Color::Black);
        map.Draw(window);
        grid.Draw(window);
        mouseTile.Draw(window);
        sidebar.Draw(window); // Draw GUI last so it stays on top!
        window.display();
    }

    cout << "i just finished off!" << endl;

    return 0;
}