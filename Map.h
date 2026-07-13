#pragma once
#include<SFML/Graphics.hpp>

#include <string>
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

	int mapHeight;
	int mapWidth;

	std::vector<std::optional<sf::Sprite>> mapSprites;
	
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