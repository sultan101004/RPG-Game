#pragma once
#include<SFML/Graphics.hpp>

#include <optional>
#include <vector>
#include "Tile.h"

class Map
{

	sf::Texture tileSheetTexture;
	std::vector<Tile> tiles;

	int tileWidth;
	int tileHeight;

	int totalTilesX;
	int totalTilesY;

	int totalTiles;

	int mapNumbers[6] = { 1, 1, 1, 25, 27, 30};
	std::optional<sf::Sprite> mapSprites[6];
public:
	Map();
	~Map();

	Map(const Map&) = delete;
	Map& operator=(const Map&) = delete;

	void Initialize();
	void Load();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};