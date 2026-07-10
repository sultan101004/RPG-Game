#pragma once
#include <SFML/Graphics.hpp>

class FrameRate
{
private:
	sf::Font font;
	sf::Text fpsText;

	float fpsTimer = 0.f;
	int frameCount = 0;

public:
	FrameRate();
	void Initialize();
	void Load();
	void Update(sf::Time deltaTime);
	void Draw(sf::RenderWindow& window);
};


