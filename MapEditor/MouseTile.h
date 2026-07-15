#pragma once
#include<SFML/Graphics.hpp>

class MouseTile
{
	std::unique_ptr<sf::Texture> tileSheet;
	std::unique_ptr<sf::Sprite> tile;

	sf::Vector2i tileSize;
	sf::Vector2i tileScale;

	sf::Vector2f offset;

	int currentTileX = 11; // Default to the 11th tile
	int currentTileY = 0;
	
	int activeLayer = 0; // 0 = Background, 1 = Foreground

public:

	MouseTile(const sf::Vector2i& tileSize, const sf::Vector2i& tileScale, const sf::Vector2f& offset);
	~MouseTile();

	void Initialize();
	void Load();
	void Update(float deltaTime, sf::Vector2f mousePosition);
	int HandleClick(sf::Vector2f mousePosition);
	void ChangeTile(int moveX, int moveY);
	void ToggleLayer();
	int GetActiveLayer() const { return activeLayer; }
	const sf::Sprite* GetTile() const { return tile.get(); }
	void Draw(sf::RenderWindow& window);
};

