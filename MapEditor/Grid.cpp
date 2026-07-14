#include "Grid.h"


Grid::Grid(const sf::Vector2f& pos,  const sf::Vector2i& cSize, const sf::Vector2i& tCells, const sf::Vector2i& skale, const sf::Color colr, int tickness)
{

	position.x = pos.x;
	position.y = pos.y;

	scale.x = static_cast<float>(skale.x);
	scale.y = static_cast<float>(skale.y);

	totalCells.x = static_cast<float>(tCells.x);
	totalCells.y = static_cast<float>(tCells.y);

	cellSize.x = static_cast<float>(cSize.x);
	cellSize.y = static_cast<float>(cSize.y);

	LineThickness = static_cast<float>(tickness);

	totalLines.x = totalCells.x + 1.f;
	totalLines.y = totalCells.y + 1.f;

	color = colr;

	hLine = new sf::RectangleShape[static_cast<size_t>(totalLines.y)];
	vLine = new sf::RectangleShape[static_cast<size_t>(totalLines.x)];

}

Grid::~Grid()
{
	delete[] hLine;
	delete[] vLine;
}

void Grid::Initialize()
{
	
	float horizontaLineLength = totalCells.x * cellSize.x * scale.x + LineThickness;
	float verticalLineLength = totalCells.y * cellSize.y * scale.y;

	for (int i = 0; i < totalCells.y + 1; i++) {

		//hLine[i].setScale(sf::Vector2f({ 5,5 }));
		hLine[i].setSize(sf::Vector2f({ horizontaLineLength, LineThickness }));
		hLine[i].setPosition(sf::Vector2f({ position + sf::Vector2f(0, static_cast<float>(i) * cellSize.y * scale.x) }));
		hLine[i].setFillColor(color);
	}

	for (int i = 0; i < totalCells.x + 1; i++) {
		
		//vLine[i].setScale(sf::Vector2f({ 5,5 }));
		vLine[i].setSize(sf::Vector2f({ LineThickness, verticalLineLength }));
		vLine[i].setPosition(sf::Vector2f({ position + sf::Vector2f(static_cast<float>(i) * cellSize.x * scale.y, 0)}));
		vLine[i].setFillColor(color);
	}

}

void Grid::Load()
{
}

void Grid::Update(float deltaTime)
{
}

void Grid::Draw(sf::RenderWindow& window)
{

	for (int i = 0; i < totalLines.y; i++) {

		window.draw(hLine[i]);
		
	}

	for (int i = 0; i < totalLines.x; i++) {

		window.draw(vLine[i]);

	}
	
}
