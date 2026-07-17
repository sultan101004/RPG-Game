#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Tile.h"

namespace sf { class Texture; class Sprite; class RenderWindow; }

class Map
{
	std::unique_ptr<sf::Texture> m_tileSheetTexture;
	std::vector<Tile> m_tiles;

	int m_tileWidth;
	int m_tileHeight;

	int m_totalTilesX;
	int m_totalTilesY;

	int m_mapHeight;
	int m_mapWidth;

	// store sprites as owning pointers to avoid requiring SFML complete type in header
	std::vector<std::unique_ptr<sf::Sprite>> m_mapSprites;

public:
	Map();
	~Map();

	Map(const Map&) = delete;
	Map& operator=(const Map&) = delete;

	void Initialize();
	void Load(const std::string& filename);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	int GetMapWidth()   const { return m_mapWidth; }
	int GetMapHeight()  const { return m_mapHeight; }
	int GetTileWidth()  const { return m_tileWidth; }
	int GetTileHeight() const { return m_tileHeight; }
};
