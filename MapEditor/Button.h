#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

namespace GUI {
    class Button {
        sf::Sprite sprite;
        sf::Text text;
        
        sf::Color defaultColor;
        sf::Color hoverColor;

        std::function<void()> onClick;
        bool isHovered = false;

    public:
        // We pass in the position, size, the text to display, the font, and the function to run when clicked!
        Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture& texture, const std::string& labelText, const sf::Font& font, std::function<void()> callback);
        ~Button();

        void Update(const sf::Vector2f& mousePosition);
        
        // Returns true if the button was clicked
        bool HandleClick(const sf::Vector2f& mousePosition);
        
        void Draw(sf::RenderWindow& window);

        // Check if mouse is touching this button
        bool IsMouseOver(const sf::Vector2f& mousePosition) const;
    };
}
