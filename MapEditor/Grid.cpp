#include "Grid.h"

Grid::Grid(const sf::Vector2f& pos, const sf::Vector2i& cSize, const sf::Vector2i& tCells, const sf::Vector2i& skale, const sf::Color colr, int tickness)
	: m_position(pos),
	  m_scale(static_cast<float>(skale.x), static_cast<float>(skale.y)),
	  m_totalCells(static_cast<float>(tCells.x), static_cast<float>(tCells.y)),
	  m_cellSize(static_cast<float>(cSize.x), static_cast<float>(cSize.y)),
	  m_lineThickness(static_cast<float>(tickness)),
	  m_totalLines(m_totalCells.x + 1.f, m_totalCells.y + 1.f),
	  m_color(colr)
{
	m_hLines.resize(static_cast<size_t>(m_totalLines.y));
	m_vLines.resize(static_cast<size_t>(m_totalLines.x));
}

Grid::~Grid()
{
}

void Grid::Initialize()
{
	float horizontaLineLength = m_totalCells.x * m_cellSize.x * m_scale.x + m_lineThickness;
	float verticalLineLength = m_totalCells.y * m_cellSize.y * m_scale.y;

	for (size_t i = 0; i < m_hLines.size(); i++) {
		m_hLines[i].setSize(sf::Vector2f({ horizontaLineLength, m_lineThickness }));
		m_hLines[i].setPosition({ m_position + sf::Vector2f(0.f, static_cast<float>(i) * m_cellSize.y * m_scale.y) });
		m_hLines[i].setFillColor(m_color);
	}

	for (size_t i = 0; i < m_vLines.size(); i++) {
		m_vLines[i].setSize(sf::Vector2f({ m_lineThickness, verticalLineLength }));
		m_vLines[i].setPosition({ m_position + sf::Vector2f(static_cast<float>(i) * m_cellSize.x * m_scale.x, 0.f) });
		m_vLines[i].setFillColor(m_color);
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
	for (const auto& line : m_hLines) {
		window.draw(line);
	}

	for (const auto& line : m_vLines) {
		window.draw(line);
	}
}
