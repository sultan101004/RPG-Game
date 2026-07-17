#include "Map.h"
#include "MapLoader.h"
#include "MapData.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

Map::Map()
	: m_tileWidth(0), m_tileHeight(0), m_totalTilesX(0), m_totalTilesY(0),
	  m_mapHeight(0), m_mapWidth(0), m_tileSheetTexture(nullptr)
{
}

Map::~Map()
{
	// unique_ptr members will be destroyed here; sf::Sprite and sf::Texture definitions are available in this translation unit
}

void Map::Initialize()
{
}

void Map::Load(const std::string& filename)
{
	MapLoader mapLoader;
	MapData md;
	mapLoader.LoadMap(filename, md);

	// Use values read from the file
	m_mapWidth = md.mapWidth;
	m_mapHeight = md.mapHeight;
	m_tileWidth = md.tileWidth;
	m_tileHeight = md.tileHeight;

	m_tileSheetTexture = std::make_unique<sf::Texture>();

	if (m_tileSheetTexture->loadFromFile(md.tilesheet))
	{
		m_totalTilesX = m_tileSheetTexture->getSize().x / md.tileWidth;
		m_totalTilesY = m_tileSheetTexture->getSize().y / md.tileHeight;

		cout << "Tilesheet dimensions: " << m_tileSheetTexture->getSize().x << "x" << m_tileSheetTexture->getSize().y << endl;
		cout << "Tilesheet texture loaded successfully!" << endl;

		m_tiles.resize(m_totalTilesX * m_totalTilesY); // resize actually creates the elements!
		for (int y = 0; y < m_totalTilesY; ++y)
		{
			for (int x = 0; x < m_totalTilesX; ++x)
			{
				int i = x + y * m_totalTilesX;

				m_tiles[i].id = i;
				m_tiles[i].position = sf::Vector2i(x * md.tileWidth, y * md.tileHeight);
			}
		}
	}
	else
	{
		cout << "Failed to load tilesheet texture!" << endl;
		return;
	}

	m_mapSprites.resize(md.data.size());

	for (size_t i = 0; i < md.data.size(); ++i)
	{
		int tileID = md.data[i];

		// -1 means empty cell — skip it, leave sprite as nullptr
		if (tileID < 0 || tileID >= static_cast<int>(m_tiles.size())) continue;

		int x = static_cast<int>(i) % m_mapWidth;
		int y = static_cast<int>(i) / m_mapWidth;

		float scaleX = static_cast<float>(md.scaleX);
		float scaleY = static_cast<float>(md.scaleY);

		// create the sprite and store ownership in unique_ptr
		m_mapSprites[i] = std::make_unique<sf::Sprite>(*m_tileSheetTexture);
		m_mapSprites[i]->setTextureRect(sf::IntRect({ m_tiles[tileID].position.x, m_tiles[tileID].position.y }, { md.tileWidth, md.tileHeight }));
		m_mapSprites[i]->setScale({ scaleX, scaleY });
		m_mapSprites[i]->setPosition({ x * md.tileWidth * scaleX, y * md.tileHeight * scaleY });
	}

}


void Map::Update(float dt)
{
}

void Map::Draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < m_mapSprites.size(); i++) {
		if (m_mapSprites[i]) {
			window.draw(*m_mapSprites[i]);
		}
	}
}
