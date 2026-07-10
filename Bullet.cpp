#include "Bullet.h"

Bullet::Bullet()
{
	speed = 300.0f;
	cout << "Bullet created" << endl;
}

Bullet::~Bullet()
{
	cout << "Bullet destroyed" << endl;
}

void Bullet::Initialize()
{
	speed = 300.0f; // Set a default speed for the bullet
}

void Bullet::Load()
{
}

void Bullet::Update(float deltaTime)
{
	shape.setPosition(shape.getPosition() + direction * speed * deltaTime);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
