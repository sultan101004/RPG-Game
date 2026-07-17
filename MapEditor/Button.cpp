#include "Button.h"
#include <iostream>

namespace GUI {

    Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture& texture, const std::string& labelText, const sf::Font& font, std::function<void()> callback)
        : onClick(callback), sprite(texture), text(font)
    {
        // Setup sprite
        sprite.setTexture(texture);
        sprite.setPosition(position);
        
        // Scale sprite to exactly match the requested button size
        sf::Vector2u texSize = texture.getSize();
        sprite.setScale(sf::Vector2f(size.x / static_cast<float>(texSize.x), size.y / static_cast<float>(texSize.y)));
        
        // Setup text
        text.setFont(font);
        text.setString(labelText);
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::White);

        // Center the text inside the button
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f));
        text.setPosition(sf::Vector2f(position.x + size.x / 2.0f, position.y + size.y / 2.0f));
    }

    Button::~Button() {}

    bool Button::IsMouseOver(const sf::Vector2f& mousePosition) const
    {
        return sprite.getGlobalBounds().contains(mousePosition);
    }

    void Button::Update(const sf::Vector2f& mousePosition)
    {
        // Check for hover
        isHovered = IsMouseOver(mousePosition);

        // Change color based on hover state
        if (isHovered) {
            sprite.setColor(sf::Color(255, 255, 255, 200)); // Make slightly transparent/bright on hover
        } else {
            sprite.setColor(sf::Color::White); // Normal
        }
    }

    bool Button::HandleClick(const sf::Vector2f& mousePosition)
    {
        if (IsMouseOver(mousePosition)) {
            if (onClick) {
                onClick(); // Run the callback function!
            }
            return true; // We successfully clicked a button!
        }
        return false;
    }

    void Button::Draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
        window.draw(text);
    }

}
