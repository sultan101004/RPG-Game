#pragma once
#include<SFML/Graphics.hpp>

#define totalLinesX 10+1
#define totalLinesY 5+1

class Grid {

	sf::RectangleShape *hLine;
	sf::RectangleShape *vLine;

	sf::Vector2f position;
	sf::Vector2f scale;
	sf::Vector2f totalCells;
	sf::Vector2f cellSize;

	sf::Vector2f totalLines;
	sf::Color color;
	float LineThickness;

public:
	Grid(const sf::Vector2f& position , const sf::Vector2i& cSize, const sf::Vector2i& tCells, const sf::Vector2i& skale, const sf::Color color, int tickness);
	~Grid();

	void Initialize();
	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window );
};