#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class MouseTile
{
	std::unique_ptr<sf::Texture> m_tileSheet;
	std::unique_ptr<sf::Sprite> m_tile;

	sf::Vector2i m_tileSize;
	sf::Vector2i m_tileScale;

	sf::Vector2f m_offset;

	int m_currentTileX;
	int m_currentTileY;
	
	int m_activeLayer; // 0 = Background, 1 = Foreground

public:

	MouseTile(const sf::Vector2i& tileSize, const sf::Vector2i& tileScale, const sf::Vector2f& offset);
	~MouseTile();

	void Initialize();
	void Load();
	void Update(float deltaTime, sf::Vector2f mousePosition);
	int HandleClick(sf::Vector2f mousePosition);
	void ChangeTile(int moveX, int moveY);
	void ToggleLayer();
	
	int GetActiveLayer() const { return m_activeLayer; }
	int GetTileID() const; // Returns the 1D tilesheet index of the currently selected tile
	const sf::Sprite* GetTile() const { return m_tile.get(); }
	
	sf::Vector2i GetCellSize() const { return m_tileSize; }
	sf::Vector2i GetScale() const { return m_tileScale; }
	sf::Vector2f GetOffset() const { return m_offset; }
	
	void Draw(sf::RenderWindow& window);
};
