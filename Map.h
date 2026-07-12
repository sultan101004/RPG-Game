#pragma once
#include<SFML/Graphics.hpp>

#include <optional>
#include <vector>

class Map
{

	sf::Texture tileSheetTexture;
	std::optional<sf::Sprite> sprite; // changed from pointer to value to avoid null dereference
	std::vector<sf::Sprite> sprites;

	int tileWidth;
	int tileHeight;

	int totalTilesX;
	int totalTilesY;

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