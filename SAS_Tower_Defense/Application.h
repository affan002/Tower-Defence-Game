#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Button.h"
#include "TileMap.h"
// #include "Player.h"

class Application {
private:
    sf::RenderWindow window;
    std::string currentState; 
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    Button startButton;
    Button quitButton;
    TileMap tileMap;
    Clock dtclock;
    float dt;
    // Player* player;

public:
    Application(): window(sf::VideoMode(1280, 720), "Main Menu"),startButton(525, 475, 200, 50, "Start"),quitButton(525, 550, 200, 50, "Quit"),currentState("MENU") { // Initial state set to "MENU"
        if (!backgroundTexture.loadFromFile("images/background_start.png")) {
            std::cout << "Failed to load background image!" << std::endl;
        }
        backgroundSprite.setTexture(backgroundTexture);

        // Scale the background to fit the window
        sf::Vector2u textureSize = backgroundTexture.getSize();
        sf::Vector2u windowSize = window.getSize();
        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
        backgroundSprite.setScale(scaleX, scaleY);
        // player = new Player();
    }
    ~Application(){
        // delete player;
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

            // Handle menu events
            if (currentState == "MENU" && event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (startButton.isClicked(mousePos)) {
                    currentState = "GAME"; // Switch to "GAME" state
                }
                if (quitButton.isClicked(mousePos)) {
                    window.close(); // Exit the application
                }
            }
            if (currentState == "END" && event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left){
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (startButton.isClicked(mousePos)) {
                    currentState = "MENU"; // Switch to "GAME" state
                }
                if (quitButton.isClicked(mousePos)) {
                    window.close(); // Exit the application
                }
            }
        }
    }

    void update() {
        if (currentState == "GAME"){
            tileMap.update(window,dt);
        }
        if (currentState == "GAME" && tileMap.getQuit()){
            currentState = "END";
        }
        if (currentState == "GAME" && tileMap.getWin()){
            currentState = "WIN";
        }
        
        if (currentState == "END"){
            backgroundTexture.loadFromFile("images/Loses.png");
            backgroundSprite.setTexture(backgroundTexture);

            // Scale the background to fit the window
            sf::Vector2u textureSize = backgroundTexture.getSize();
            sf::Vector2u windowSize = window.getSize();
            float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
            float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
            backgroundSprite.setScale(scaleX, scaleY);
        }
        if (currentState == "WIN"){
            backgroundTexture.loadFromFile("images/Win.png");
            backgroundSprite.setTexture(backgroundTexture);

            // Scale the background to fit the window
            sf::Vector2u textureSize = backgroundTexture.getSize();
            sf::Vector2u windowSize = window.getSize();
            float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
            float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
            backgroundSprite.setScale(scaleX, scaleY);
        }
    }

    void render() {
        window.clear();

        if (currentState == "MENU") {
            // Render menu
            window.draw(backgroundSprite); // Draw the background
            startButton.draw(window);
            quitButton.draw(window);
        } else if (currentState == "GAME") {
            // Render game
            tileMap.draw(window);
        }
        else if (currentState == "END" || currentState == "WIN"){
            window.draw(backgroundSprite);
        }
        // player->draw(window);
        window.display();
    }
    void UpdateDT(){
    this->dt = this->dtclock.restart().asSeconds();
}
};