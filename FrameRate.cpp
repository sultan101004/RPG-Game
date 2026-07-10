#include<iostream>

#include "FrameRate.h"

FrameRate::FrameRate() : fpsText(font) {}

void FrameRate::Initialize()
{
}

void FrameRate::Load()
{
    if (!font.openFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cout << "Error loading font!" << std::endl;
    }
    else {
        // Configure the member variable, don't create a local one!
        fpsText.setFont(font);
        fpsText.setCharacterSize(24);
        fpsText.setFillColor(sf::Color::Yellow);
        fpsText.setPosition({ 10.f, 10.f });
    }
}

void FrameRate::Update(sf::Time deltaTimer)
{
    float deltaTime = deltaTimer.asSeconds();

    // Smooth FPS Calculation
    fpsTimer += deltaTime;
    frameCount++;

    if (fpsTimer >= 0.5f) {
        float fps = frameCount / fpsTimer;
        fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
        fpsTimer = 0.f;
        frameCount = 0;
    }
}

void FrameRate::Draw(sf::RenderWindow& window)
{
    window.draw(fpsText); // Draw UI elements on top of game textures
}
