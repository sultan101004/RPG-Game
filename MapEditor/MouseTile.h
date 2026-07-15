#pragma once
#include<SFML/Graphics.hpp>

class MouseTile
{
	std::unique_ptr<sf::Texture> tileSheet;
	std::unique_ptr<sf::Sprite> tile;

	sf::Vector2i tileSize;
	sf::Vector2i tileScale;

	sf::Vector2f offset;

public:

	MouseTile(const sf::Vector2i& tileSize, const sf::Vector2i& tileScale, const sf::Vector2f& offset);
	~MouseTile();

	void Initialize();
	void Load();
	void Update(float deltaTime, sf::Vector2f mousePosition);
	int HandleClick(sf::Vector2f mousePosition);
	const sf::Sprite* GetTile() const { return tile.get(); }
	void Draw(sf::RenderWindow& window);
};

