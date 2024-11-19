#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;

public:
    Button(float x, float y, float width, float height, const std::string& buttonText) {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(sf::Color::Black);

        if (!font.loadFromFile("fonts/upheavtt.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(
            x + (width - text.getLocalBounds().width) / 2,
            y + (height - text.getLocalBounds().height) / 2
        );
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

    bool isClicked(sf::Vector2i mousePos) {
        return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }
};