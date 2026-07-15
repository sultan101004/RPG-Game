#include "Mep.h"

Mep::Mep()
{
}

Mep::~Mep()
{
}

void Mep::Initialize()
{
	// We resize the vectors to hold exactly MAP_SIZE slots. 
	// Because they are unique_ptrs, they all safely start as 'nullptr' until you give them a texture!
	bgSprites.resize(MAP_SIZE);
	fgSprites.resize(MAP_SIZE);
}

void Mep::Load()
{
}

void Mep::Update(double deltaTime, sf::Vector2f mousePosition)
{
}

void Mep::PlaceTile(int index, int layer, const sf::Sprite& sourceSprite)
{
	if (index >= 0 && index < MAP_SIZE) {
		// Grab a reference to the correct layer based on the layer integer (0 = bg, 1 = fg)
		std::vector<std::unique_ptr<sf::Sprite>>& targetLayer = (layer == 0) ? bgSprites : fgSprites;

		// 1. Create the new sprite and copy the texture
		targetLayer[index] = std::make_unique<sf::Sprite>(sourceSprite.getTexture());
		
		// 2. Copy the exact position, scale, and texture rect (which part of the image it shows)
		targetLayer[index]->setTextureRect(sourceSprite.getTextureRect());
		targetLayer[index]->setScale(sourceSprite.getScale());
		targetLayer[index]->setPosition(sourceSprite.getPosition());
	}
}

void Mep::Draw(sf::RenderWindow& window)
{
	// Draw background first!
	for (int i = 0; i < MAP_SIZE; i++) {
		if (bgSprites[i]) {
			window.draw(*bgSprites[i]);
		}
	}
	
	// Draw foreground second (so it renders ON TOP of the background)
	for (int i = 0; i < MAP_SIZE; i++) {
		if (fgSprites[i]) {
			window.draw(*fgSprites[i]);
		}
	}
}