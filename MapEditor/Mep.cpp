#include "Mep.h"

Mep::Mep(int width, int height)
    : m_width(width), m_height(height)
{
    int size = m_width * m_height;
    m_bgSprites.resize(size);
    m_fgSprites.resize(size);
    m_bgTileIDs.assign(size, -1); // fill with -1 (empty)
    m_fgTileIDs.assign(size, -1);
}

Mep::~Mep()
{
}

void Mep::PlaceTile(int index, int layer, const sf::Sprite& sourceSprite, int tileID)
{
    if (index >= 0 && index < GetSize()) {
        std::vector<std::unique_ptr<sf::Sprite>>& targetLayer = (layer == 0) ? m_bgSprites : m_fgSprites;
        std::vector<int>&                         targetIDs   = (layer == 0) ? m_bgTileIDs : m_fgTileIDs;

        // Store the tilesheet ID so we can serialize it later
        targetIDs[index] = tileID;

        // Create the new sprite and copy all visual properties from the preview tile
        targetLayer[index] = std::make_unique<sf::Sprite>(sourceSprite.getTexture());
        targetLayer[index]->setTextureRect(sourceSprite.getTextureRect());
        targetLayer[index]->setScale(sourceSprite.getScale());
        targetLayer[index]->setPosition(sourceSprite.getPosition());
    }
}

void Mep::Draw(sf::RenderWindow& window)
{
    int size = GetSize();
    
    // Draw background first!
    for (int i = 0; i < size; i++) {
        if (m_bgSprites[i]) {
            window.draw(*m_bgSprites[i]);
        }
    }

    // Draw foreground second (so it renders ON TOP of the background)
    for (int i = 0; i < size; i++) {
        if (m_fgSprites[i]) {
            window.draw(*m_fgSprites[i]);
        }
    }
}