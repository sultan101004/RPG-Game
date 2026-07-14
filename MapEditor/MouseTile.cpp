#include "MouseTile.h"
#include <iostream>

using namespace std;

MouseTile::MouseTile(const sf::Vector2i& tileSize, const sf::Vector2i& tileScale)
{
    // 1. Allocate memory for the texture
    tileSheet = std::make_unique<sf::Texture>();
    this->tileSize = tileSize;
    this->tileScale = tileScale;
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
    tile->setScale(sf::Vector2f({ 5,5 }));
}

void MouseTile::Update(float deltaTime, sf::Vector2f mousePosition)
{
    //float scaleX = tile->getScale().x;
    //float scaleY = tile->getScale().y;

    int intX = static_cast<int>(mousePosition.x / (16.f * static_cast<float>(tileScale.x)));
    float xx = static_cast<float>(intX) * (16.f * static_cast<float>(tileScale.x));

    int intY = static_cast<int>(mousePosition.y / (16.f * static_cast<float>(tileScale.y)));
    float yy = static_cast<float>(intY) * (16.f * static_cast<float>(tileScale.y));

    if (tile) {
        tile->setPosition(sf::Vector2f(xx, yy));
    }
}

void MouseTile::Draw(sf::RenderWindow& window)
{
    if (tile) {
        window.draw(*tile);
    }
}
