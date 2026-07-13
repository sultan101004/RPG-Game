#include "Map.h"
#include "MapLoader.h"
#include "MapData.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

Map::Map() 
{
	totalTilesX = 0;
	totalTilesY = 0;

	mapHeight = 2; // Default if not computed
	mapWidth = 3;
}

Map::~Map()
{
}

void Map::Initialize()
{
}

void Map::Load(const std::string& filename)
{
	MapLoader mapLoader;
	MapData md;
	mapLoader.LoadMap(filename, md);

	if (tileSheetTexture.loadFromFile(md.tilesheet))
	{
		totalTilesX = tileSheetTexture.getSize().x / md.tileWidth;
		totalTilesY = tileSheetTexture.getSize().y / md.tileHeight;

		cout << "Tilesheet dimensions: " << tileSheetTexture.getSize().x << "x" << tileSheetTexture.getSize().y << endl;
		cout << "Tilesheet texture loaded successfully!" << endl;

		tiles.resize(totalTilesX * totalTilesY); // resize actually creates the elements!
		for (int y = 0; y < totalTilesY; ++y)
		{
			for (int x = 0; x < totalTilesX; ++x)
			{
				int i = x + y * totalTilesX;

				tiles[i].id = i;
				tiles[i].position = sf::Vector2i(x * md.tileWidth, y * md.tileHeight);
			}
		}
	}
	else
	{
		cout << "Failed to load tilesheet texture!" << endl;
		return;
	}

	mapSprites.resize(md.data.size());

	for (size_t i = 0; i < md.data.size(); ++i)
	{
		int x = i % mapWidth;
		int y = i / mapWidth;
		
		int index = md.data[i]; // Adjust for 0-based index

		// You MUST use emplace() to create the sprite before you can use ->
		mapSprites[i].emplace(tileSheetTexture);
		mapSprites[i]->setTextureRect(sf::IntRect({ tiles[index].position.x, tiles[index].position.y }, { md.tileWidth, md.tileHeight }));
		mapSprites[i]->setScale({ 3.0f, 3.0f });
		mapSprites[i]->setPosition({ x * md.tileWidth * mapSprites[i]->getScale().x, y * md.tileHeight * mapSprites[i]->getScale().y}); // Adjusted for scaling
	}

}


void Map::Update(float dt)
{
}

void Map::Draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < mapSprites.size(); i++) {
		if (mapSprites[i].has_value()) {
			window.draw(*mapSprites[i]);
		}
	}
}
