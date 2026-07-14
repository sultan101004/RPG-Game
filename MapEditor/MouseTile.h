#pragma once
#include<SFML/Graphics.hpp>

class MouseTile
{
	std::unique_ptr<sf::Texture> tileSheet;
	std::unique_ptr<sf::Sprite> tile;

	sf::Vector2i tileSize;
	sf::Vector2i tileScale;
public:

	MouseTile(const sf::Vector2i& tileSize, const sf::Vector2i& tileScale);
	~MouseTile();

	void Initialize();
	void Load();
	void Update(float deltaTime, sf::Vector2f mousePosition);
	void Draw(sf::RenderWindow& window);
};

