#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

const int TILE_SIZE = 32; // Size of each tile in pixels
const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 20;

// Define the path layout using a grid
const std::vector<std::vector<int>> levelMap = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    
};

class TileMap {
private:
    sf::Texture grassTexture;
    sf::Texture pathTexture;
    sf::Sprite grassSprite;
    sf::Sprite pathSprite;

public:
    TileMap() {
        if (!grassTexture.loadFromFile("images/grass.jpeg")) {
            std::cerr << "Failed to load grass texture!" << std::endl;
        }
        if (!pathTexture.loadFromFile("images/tile_1.png")) {
            std::cerr << "Failed to load path texture!" << std::endl;
        }

        grassSprite.setTexture(grassTexture);
        pathSprite.setTexture(pathTexture);
    }

    void draw(sf::RenderWindow& window) {
        for (size_t y = 0; y < levelMap.size(); ++y) {
            for (size_t x = 0; x < levelMap[y].size(); ++x) {
                if (levelMap[y][x] == 0) {
                    grassSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    window.draw(grassSprite);
                } else if (levelMap[y][x] == 1) {
                    pathSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                    window.draw(pathSprite);
                }
            }
        }
    }
};
class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;

public:
    Button(float x, float y, float width, float height, const std::string& buttonText) {
        shape.setPosition(x, y);
        shape.setSize(sf::Vector2f(width, height));
        shape.setFillColor(sf::Color::Transparent);

        if (!font.loadFromFile("fonts/upheavtt.ttf")) {
            std::cerr << "Failed to load font!" << std::endl;
        }

        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Transparent);
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

class Application {
private:
    sf::RenderWindow window;
    enum class State { MENU, GAME } currentState;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Button startButton;
    Button quitButton;
    TileMap tileMap;

public:
    Application()
        : window(sf::VideoMode(640, 480), "Main Menu"),
          startButton(220, 300, 200, 50, "Start"),
          quitButton(220, 350, 200, 50, "Quit"),
          currentState(State::MENU) {
        if (!backgroundTexture.loadFromFile("images/background_start.png")) {
            std::cerr << "Failed to load background image!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        // Scale the background to fit the window
        sf::Vector2u textureSize = backgroundTexture.getSize();
        sf::Vector2u windowSize = window.getSize();
        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
        backgroundSprite.setScale(scaleX, scaleY);
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (currentState == State::MENU && event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (startButton.isClicked(mousePos)) {
                    currentState = State::GAME; // Switch to game state
                }
                if (quitButton.isClicked(mousePos)) {
                    window.close();
                }
            }
        }
    }

    void update() {
        // Any logic updates can go here
    }

    void render() {
        window.clear();

        if (currentState == State::MENU) {
            // Render menu
            window.draw(backgroundSprite); // Draw the background
            startButton.draw(window);
            quitButton.draw(window);
        } else if (currentState == State::GAME) {
            // Render game
            tileMap.draw(window);
        }

        window.display();
    }
};

int main() {
    Application app;
    app.run();
    return 0;
}
