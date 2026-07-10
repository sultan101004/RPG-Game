#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;

class Bullet
{
public:
	float speed;
	float fireRate;
	sf::Vector2f direction;
	

public:
	sf::RectangleShape shape;
	Bullet();
	~Bullet();
	void Initialize();
	void Load();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void setPosition(const sf::Vector2f& position) { shape.setPosition(position); }
	void setSize(const sf::Vector2f& size) { shape.setSize(size); }
	void setFillColor(const sf::Color& color) { shape.setFillColor(color); }

};

