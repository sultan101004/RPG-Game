#include "MouseTile.h"
#include <iostream>

using namespace std;

MouseTile::MouseTile(const sf::Vector2i& tileSize, const sf::Vector2i& tileScale, const sf::Vector2f& offset)
{
    // 1. Allocate memory for the texture
    tileSheet = std::make_unique<sf::Texture>();
    this->tileSize = tileSize;
    this->tileScale = tileScale;
    this->offset = offset;
}

MouseTile::~MouseTile()
{
}

void MouseTile::Initialize()
{
}

void MouseTile::Load()
{
    // 2. Load the texture from the file (using forward slashes to avoid escape character warnings)
    if (!tileSheet->loadFromFile("../Assets/World/Prison/tilesheet.png")) {
        std::cout << "Error loading texture!" << std::endl;
        return;
    }
    // 3. Apply the texture to the sprite
    // SFML 3 requires a texture to create a sprite, so we create the sprite HERE
    tile = std::make_unique<sf::Sprite>(*tileSheet);
    tile->setTextureRect(sf::IntRect({ 11*tileSize.x, 0 }, { tileSize.x, tileSize.y }));
    tile->setScale(sf::Vector2f({ 4,4 }));
}

void MouseTile::Update(float deltaTime, sf::Vector2f mousePosition)
{
    float effectiveTileSizeX = tileSize.x * static_cast<float>(tileScale.x);
    float effectiveTileSizeY = tileSize.y * static_cast<float>(tileScale.y);

    // 1. Subtract offset to find relative mouse position
    float relativeX = mousePosition.x - offset.x;
    float relativeY = mousePosition.y - offset.y;

    // 2. Use std::floor to correctly handle negative numbers (if mouse goes left/above grid)
    int gridIndexX = static_cast<int>(std::floor(relativeX / effectiveTileSizeX));
    int gridIndexY = static_cast<int>(std::floor(relativeY / effectiveTileSizeY));

    // 3. Add the offset back to the final position
    float xx = offset.x + (static_cast<float>(gridIndexX) * effectiveTileSizeX);
    float yy = offset.y + (static_cast<float>(gridIndexY) * effectiveTileSizeY);

    if (tile) {
        tile->setPosition(sf::Vector2f(xx, yy));
    }
}

int MouseTile::HandleClick(sf::Vector2f mousePosition)
{
    float effectiveTileSizeX = tileSize.x * static_cast<float>(tileScale.x);
    float effectiveTileSizeY = tileSize.y * static_cast<float>(tileScale.y);

    float relativeX = mousePosition.x - offset.x;
    float relativeY = mousePosition.y - offset.y;

    int intX = static_cast<int>(std::floor(relativeX / effectiveTileSizeX));
    int intY = static_cast<int>(std::floor(relativeY / effectiveTileSizeY));

    // Make sure the click is actually inside the 10x5 grid!
    if (intX >= 0 && intX < 10 && intY >= 0 && intY < 5) {

        // Calculate the 1D index (width is 10)
        int index = intX + (intY * 10);
        
        // Ensure the preview tile is snapped to the EXACT position they clicked
        // so that Mep can copy its perfect coordinates!
        float xx = offset.x + (static_cast<float>(intX) * effectiveTileSizeX);
        float yy = offset.y + (static_cast<float>(intY) * effectiveTileSizeY);
        if (tile) {
            tile->setPosition(sf::Vector2f(xx, yy));
        }

        cout << "Clicked Cell: " << intX << " " << intY << " | Array Index: " << index << endl;
        return index;
    }
    else {
        cout << "Clicked outside the grid!" << endl;
        return -1;
    }
}

void MouseTile::Draw(sf::RenderWindow& window)
{
    if (tile) {
        window.draw(*tile);
    }
}
