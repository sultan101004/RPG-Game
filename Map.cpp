#include "Map.h"
#include<SFML/Graphics.hpp>
#include<iostream>


using namespace std;

Map::Map() 
{
	tileWidth = 16;
	tileHeight = 16;
	totalTilesX = 0;
	totalTilesY = 0;

	totalTiles = 0;
	mapHeight = 2;
	mapWidth = 3;

}

Map::~Map()
{
}

void Map::Initialize()
{
}

void Map::Load()
{
	if (tileSheetTexture.loadFromFile("Assets/World/Prison/tilesheet.png"))
	{
		totalTilesX = tileSheetTexture.getSize().x / tileWidth;
		totalTilesY = tileSheetTexture.getSize().y / tileHeight;

		cout << "Tilesheet dimensions: " << tileSheetTexture.getSize().x << "x" << tileSheetTexture.getSize().y << endl;

		cout << "Tilesheet texture loaded successfully!" << endl;

		tiles.resize(totalTilesX * totalTilesY); // resize actually creates the elements!
		for (int y = 0; y < totalTilesY; ++y)
		{
			for (int x = 0; x < totalTilesX; ++x)
			{
				int i = x + y * totalTilesX;

				tiles[i].id = i;
				//tiles[i].texture = &tileSheetTexture;
				tiles[i].position = sf::Vector2i(x * tileWidth, y * tileHeight);

				//tiles[i].rect = sf::IntRect({ x * tileWidth, y * tileHeight }, { tileWidth, tileHeight });
				//tiles[i].sprite.emplace(tileSheetTexture);
				//tiles[i].sprite->setTextureRect({ {x * tileWidth, y * tileHeight}, {tileWidth, tileHeight} });
				//tiles[i].sprite->setScale({ 3.0f, 3.0f });
				//tiles[i].sprite->setPosition({ x * tileWidth * 3.f, y * tileHeight * 3.f });
			}
		}
	}
	else
	{
		cout << "Failed to load tilesheet texture!" << endl;
		// Handle error loading texture
	}

	for (int y = 0; y < mapHeight; ++y)
	{
		for (int x = 0; x < mapWidth; ++x)
		{
			int i = x + y * mapWidth;
			cout << "Tile ID: " << tiles[i].id << " at position (" << x << ", " << y << ")" << endl;
			
			int index = mapNumbers[i]; // Adjust for 0-based index

			// You MUST use emplace() to create the sprite before you can use ->
			mapSprites[i].emplace(tileSheetTexture);
			mapSprites[i]->setTextureRect(sf::IntRect({ tiles[index].position.x, tiles[index].position.y }, { tileWidth, tileHeight }));
			mapSprites[i]->setScale({ 3.0f, 3.0f });
			mapSprites[i]->setPosition({ x * tileWidth * mapSprites[i]->getScale().x, y * tileHeight * mapSprites[i]->getScale().y}); // Adjusted for scaling
 		}
	}

}


void Map::Update(float dt)
{
}

void Map::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAP_ARRAY_SIZE; i++) {
		if (mapSprites[i].has_value()) {
			window.draw(*mapSprites[i]);
		}
	}
}
