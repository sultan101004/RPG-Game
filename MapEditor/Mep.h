#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Mep
{
    // --- Configuration (set at construction, never changed) ---
    int m_width;
    int m_height;

    // --- State ---
    std::vector<std::unique_ptr<sf::Sprite>> m_bgSprites;
    std::vector<std::unique_ptr<sf::Sprite>> m_fgSprites;

    // Parallel arrays storing the tilesheet ID for each placed tile.
    // -1 means the cell is empty (nothing placed there yet).
    std::vector<int> m_bgTileIDs;
    std::vector<int> m_fgTileIDs;

public:
    Mep(int width, int height);
    ~Mep();

    int GetWidth()  const { return m_width; }
    int GetHeight() const { return m_height; }
    int GetSize()   const { return m_width * m_height; }

    // tileID is the 1D index into the tilesheet
    void PlaceTile(int index, int layer, const sf::Sprite& sourceSprite, int tileID);

    // Read-only access to the tile ID data for serialization
    const std::vector<int>& GetBgData() const { return m_bgTileIDs; }
    const std::vector<int>& GetFgData() const { return m_fgTileIDs; }

    /// <summary>
    /// Draws mapSprites for the vector mapSprites
    /// </summary>
    /// <param name="window">OUT DATA - returns a display of sprites. </param>
    void Draw(sf::RenderWindow& window);
};
