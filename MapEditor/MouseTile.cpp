#include "MouseTile.h"
#include <iostream>
#include <cmath>

using namespace std;

MouseTile::MouseTile(const sf::Vector2i& tileSize, const sf::Vector2i& tileScale, const sf::Vector2f& offset)
    : m_tileSheet(std::make_unique<sf::Texture>()),
      m_tileSize(tileSize),
      m_tileScale(tileScale),
      m_offset(offset),
      m_currentTileX(0),
      m_currentTileY(0),
      m_activeLayer(0)
{
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
    if (!m_tileSheet->loadFromFile("../Assets/World/Prison/tilesheet.png")) {
        std::cout << "Error loading texture!" << std::endl;
        return;
    }
    // 3. Apply the texture to the sprite
    // SFML 3 requires a texture to create a sprite, so we create the sprite HERE
    m_tile = std::make_unique<sf::Sprite>(*m_tileSheet);
    m_tile->setTextureRect(sf::IntRect({ m_currentTileX * m_tileSize.x, m_currentTileY * m_tileSize.y }, { m_tileSize.x, m_tileSize.y }));
    m_tile->setScale(sf::Vector2f(static_cast<float>(m_tileScale.x), static_cast<float>(m_tileScale.y)));
}

void MouseTile::Update(float deltaTime, sf::Vector2f mousePosition)
{
    float effectiveTileSizeX = m_tileSize.x * static_cast<float>(m_tileScale.x);
    float effectiveTileSizeY = m_tileSize.y * static_cast<float>(m_tileScale.y);

    // 1. Subtract offset to find relative mouse position
    float relativeX = mousePosition.x - m_offset.x;
    float relativeY = mousePosition.y - m_offset.y;

    // 2. Use std::floor to correctly handle negative numbers (if mouse goes left/above grid)
    int gridIndexX = static_cast<int>(std::floor(relativeX / effectiveTileSizeX));
    int gridIndexY = static_cast<int>(std::floor(relativeY / effectiveTileSizeY));

    // 3. Add the offset back to the final position
    float xx = m_offset.x + (static_cast<float>(gridIndexX) * effectiveTileSizeX);
    float yy = m_offset.y + (static_cast<float>(gridIndexY) * effectiveTileSizeY);

    if (m_tile) {
        m_tile->setPosition(sf::Vector2f(xx, yy));
    }
}

int MouseTile::HandleClick(sf::Vector2f mousePosition)
{
    float effectiveTileSizeX = m_tileSize.x * static_cast<float>(m_tileScale.x);
    float effectiveTileSizeY = m_tileSize.y * static_cast<float>(m_tileScale.y);

    float relativeX = mousePosition.x - m_offset.x;
    float relativeY = mousePosition.y - m_offset.y;

    int intX = static_cast<int>(std::floor(relativeX / effectiveTileSizeX));
    int intY = static_cast<int>(std::floor(relativeY / effectiveTileSizeY));

    // Make sure the click is actually inside the 10x5 grid!
    if (intX >= 0 && intX < 10 && intY >= 0 && intY < 5) {

        // Calculate the 1D index (width is 10)
        int index = intX + (intY * 10);
        
        // Ensure the preview tile is snapped to the EXACT position they clicked
        // so that Mep can copy its perfect coordinates!
        float xx = m_offset.x + (static_cast<float>(intX) * effectiveTileSizeX);
        float yy = m_offset.y + (static_cast<float>(intY) * effectiveTileSizeY);
        if (m_tile) {
            m_tile->setPosition(sf::Vector2f(xx, yy));
        }

        cout << "Clicked Cell: " << intX << " " << intY << " | Array Index: " << index << endl;
        return index;
    }
    else {
        cout << "Clicked outside the grid!" << endl;
        return -1;
    }
}

void MouseTile::ChangeTile(int moveX, int moveY)
{
    // Make sure we have a texture loaded before doing math
    if (!m_tileSheet) return;

    m_currentTileX += moveX;
    m_currentTileY += moveY;

    // Calculate exactly how many tiles fit in the loaded image!
    int maxTilesX = m_tileSheet->getSize().x / m_tileSize.x;
    int maxTilesY = m_tileSheet->getSize().y / m_tileSize.y;

    // Prevent going into negative tile indices (left/top edges)
    if (m_currentTileX < 0) m_currentTileX = 0;
    if (m_currentTileY < 0) m_currentTileY = 0;

    // Prevent going past the actual image width/height (right/bottom edges)
    // We use - 1 because indices start at 0
    if (m_currentTileX >= maxTilesX) m_currentTileX = maxTilesX - 1;
    if (m_currentTileY >= maxTilesY) m_currentTileY = maxTilesY - 1;

    // Update the cutout rectangle!
    if (m_tile) {
        m_tile->setTextureRect(sf::IntRect({ m_currentTileX * m_tileSize.x, m_currentTileY * m_tileSize.y }, { m_tileSize.x, m_tileSize.y }));
        std::cout << "Selected Tile: [" << m_currentTileX << ", " << m_currentTileY << "]" << std::endl;
    }
}

void MouseTile::ToggleLayer()
{
    m_activeLayer = (m_activeLayer == 0) ? 1 : 0;
    std::cout << "--- Switched to Layer: " << (m_activeLayer == 0 ? "BACKGROUND" : "FOREGROUND") << " ---" << std::endl;
}

void MouseTile::Draw(sf::RenderWindow& window)
{
    if (m_tile) {
        window.draw(*m_tile);
    }
}

int MouseTile::GetTileID() const
{
    if (!m_tileSheet) return 0;
    // How many tiles fit across the width of the tilesheet image?
    int tilesPerRow = m_tileSheet->getSize().x / m_tileSize.x;
    // Convert 2D (X, Y) tile coordinate into a single 1D index
    return m_currentTileY * tilesPerRow + m_currentTileX;
}
