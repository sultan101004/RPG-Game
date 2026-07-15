#include "Mep.h"

Mep::Mep()
{
}

Mep::~Mep()
{
}

void Mep::Initialize()
{
	// We resize the vector to hold exactly MAP_SIZE slots. 
	// Because they are unique_ptrs, they all safely start as 'nullptr' until you give them a texture!
	mapSprites.resize(MAP_SIZE);
}

void Mep::Load()
{
}

void Mep::Update(double deltaTime, sf::Vector2f mousePosition)
{
}

void Mep::PlaceTile(int index, const sf::Sprite& sourceSprite)
{
	if (index >= 0 && index < MAP_SIZE) {
		// 1. Create the new sprite and copy the texture
		mapSprites[index] = std::make_unique<sf::Sprite>(sourceSprite.getTexture());
		
		// 2. Copy the exact position, scale, and texture rect (which part of the image it shows)
		mapSprites[index]->setTextureRect(sourceSprite.getTextureRect());
		mapSprites[index]->setScale(sourceSprite.getScale());
		mapSprites[index]->setPosition(sourceSprite.getPosition());
	}
}

void Mep::Draw(sf::RenderWindow& window)
{
	for (int i = 0;i < MAP_SIZE; i++) {
		if (mapSprites[i]) {
			window.draw(*mapSprites[i]);
		}
	}
	/// <sumamry>
	/// Draws mapSprites for the vector mapSprites
	/// </summary>
	/// <param name="window">OUT DATA - returns a display of sprites. </param>
	/// <returns></returns>

}
