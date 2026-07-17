#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Button.h"

namespace GUI {
    class Panel {
        sf::RectangleShape background;
        std::vector<std::unique_ptr<Button>> buttons;

    public:
        Panel(const sf::Vector2f& position, const sf::Vector2f& size);
        ~Panel();

        // Add a button to the panel
        void AddButton(std::unique_ptr<Button> button);

        void Update(const sf::Vector2f& mousePosition);
        
        // Returns true if the click was consumed by the panel or its buttons
        bool HandleClick(const sf::Vector2f& mousePosition);
        
        void Draw(sf::RenderWindow& window);

        bool IsMouseOver(const sf::Vector2f& mousePosition) const;
    };
}
