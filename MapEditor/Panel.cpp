#include "Panel.h"

namespace GUI {

    Panel::Panel(const sf::Vector2f& position, const sf::Vector2f& size)
    {
        background.setPosition(position);
        background.setSize(size);
        background.setFillColor(sf::Color(40, 40, 40, 240)); // Dark, slightly transparent
        background.setOutlineColor(sf::Color(100, 100, 100));
        background.setOutlineThickness(2.0f);
    }

    Panel::~Panel() {}

    void Panel::AddButton(std::unique_ptr<Button> button)
    {
        buttons.push_back(std::move(button));
    }

    bool Panel::IsMouseOver(const sf::Vector2f& mousePosition) const
    {
        return background.getGlobalBounds().contains(mousePosition);
    }

    void Panel::Update(const sf::Vector2f& mousePosition)
    {
        for (auto& button : buttons) {
            button->Update(mousePosition);
        }
    }

    bool Panel::HandleClick(const sf::Vector2f& mousePosition)
    {
        // First check if the mouse is even over the panel
        if (IsMouseOver(mousePosition)) {
            // Check if any button was clicked
            for (auto& button : buttons) {
                if (button->HandleClick(mousePosition)) {
                    return true; // Click was handled by a button
                }
            }
            // Even if they missed the buttons, they clicked the panel backdrop!
            // We return true so they don't accidentally place a tile under the panel.
            return true; 
        }
        return false; // Click was outside the panel entirely
    }

    void Panel::Draw(sf::RenderWindow& window)
    {
        window.draw(background);
        for (auto& button : buttons) {
            button->Draw(window);
        }
    }

}
