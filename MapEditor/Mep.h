#pragma once
#include<SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "MouseTile.h"

#define MAP_SIZE 50
class Mep
{
	
	std::vector<std::unique_ptr<sf::Sprite>> mapSprites;

public:
	Mep();
	~Mep();

	void Initialize();
	void Load();
	void Update(double deltaTime, sf::Vector2f mousePosition);
	void PlaceTile(int index, const sf::Sprite& sourceSprite);
	/// <sumamry>
	/// Draws mapSprites for the vector mapSprites
	/// </summary>
	/// <param name="window">OUT DATA - returns a display of sprites. </param>
	/// <returns></returns>
	void Draw(sf::RenderWindow & window);
};

