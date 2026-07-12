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

		sprites.reserve(totalTilesX * totalTilesY);
		for (int i = 0; i < totalTilesX * totalTilesY; ++i)
		{
			int xIndex = i % totalTilesX;
			int yIndex = i / totalTilesX;

			sprites.emplace_back(tileSheetTexture);
			sprites.back().setTextureRect({ {xIndex * tileWidth, yIndex * tileHeight}, {tileWidth, tileHeight} });
			sprites.back().setScale({ 3.0f, 3.0f });
			sprites.back().setPosition({ xIndex * tileWidth * 3.f, yIndex * tileHeight * 3.f });
		}
	}
	else
	{
		cout << "Failed to load tilesheet texture!" << endl;
		// Handle error loading texture
	}
}


void Map::Update(float dt)
{
}

void Map::Draw(sf::RenderWindow& window)
{
	for (const auto& sprite : sprites)
	{
		window.draw(sprite);
	}
}
