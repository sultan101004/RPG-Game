#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Grid {
	std::vector<sf::RectangleShape> m_hLines;
	std::vector<sf::RectangleShape> m_vLines;

	sf::Vector2f m_position;
	sf::Vector2f m_scale;
	sf::Vector2f m_totalCells;
	sf::Vector2f m_cellSize;

	sf::Vector2f m_totalLines;
	sf::Color m_color;
	float m_lineThickness;

public:
	Grid(const sf::Vector2f& position, const sf::Vector2i& cSize, const sf::Vector2i& tCells, const sf::Vector2i& skale, const sf::Color color, int tickness);
	~Grid();

	void Initialize();
	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow &window);
};