#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Tile.h"

namespace sf { class Texture; class Sprite; class RenderWindow; }

class Map
{
	std::unique_ptr<sf::Texture> tileSheetTexture;
	std::vector<Tile> tiles;

	int tileWidth;
	int tileHeight;

	int totalTilesX;
	int totalTilesY;

	int mapHeight;
	int mapWidth;

	// store sprites as owning pointers to avoid requiring SFML complete type in header
	std::vector<std::unique_ptr<sf::Sprite>> mapSprites;

public:
	Map();
	~Map();

	Map(const Map&) = delete;
	Map& operator=(const Map&) = delete;

	void Initialize();
	void Load(const std::string& filename);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};
