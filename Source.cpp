#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    // -------------------------- INITIALIZE -------------------------------- //

    RenderWindow window(VideoMode({ 800, 600}), "SFML works!");

    // Circle Shape
    CircleShape face(50.f);
    face.setFillColor(Color::Green);
    face.setPosition(sf::Vector2f(100, 100));
    face.setOutlineThickness(5.f);
    face.setOutlineColor(sf::Color::Blue);

    // body Shape
    RectangleShape body(sf::Vector2f(150.f, 40.f));
    body.setFillColor(sf::Color::Blue);
    body.setPosition(sf::Vector2f(170.f, 200.f));
    body.setRotation(sf::degrees(90));


    // handL Shape
    RectangleShape handL(sf::Vector2f(70.f, 30.f));
    handL.setFillColor(sf::Color::Yellow);
    handL.setPosition(sf::Vector2f(170.f, 200.f));
    //handL.setRotation(sf::degrees(90));

    // handR Shape
    RectangleShape handR(sf::Vector2f(70.f, 30.f));
    handR.setFillColor(sf::Color::Yellow);
    handR.setPosition(sf::Vector2f(60.f, 200.f));
    //handR.setRotation(sf::degrees(90));

    // FeetL Shape
    RectangleShape FeetL(sf::Vector2f(100.f, 30.f));
    FeetL.setFillColor(sf::Color::Green);
    FeetL.setPosition(sf::Vector2f(130.f, 350.f));
    FeetL.setRotation(sf::degrees(90));

    // FeetR Shape
    RectangleShape FeetR(sf::Vector2f(100.f, 30.f));
    FeetR.setFillColor(sf::Color::Green);
    FeetR.setPosition(sf::Vector2f(200.f, 350.f));
    FeetR.setRotation(sf::degrees(90));


    // -------------------------- INITIALIZE -------------------------------- //


    // main game loop
    while (window.isOpen())
    {
        // -------------------------- UPDATE -------------------------------- //

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>())
                window.close();
        }

        // -------------------------- UPDATE -------------------------------- //


        // -------------------------- DRAW -------------------------------- //
        window.clear(sf::Color::Black);
        window.draw(face);
        window.draw(body);
        window.draw(handL);
        window.draw(handR);
        window.draw(FeetL);
        window.draw(FeetR);
        window.display();
        // -------------------------- DRAW -------------------------------- //

    }
}
