#include "Game.h"

Game::Game(){

    std::string Name = "SAS Tower Defense";
    int screen_width = 1280;
    int screen_height = 720;
    window = new sf::RenderWindow(sf::VideoMode(screen_width, screen_height), Name);
    
    

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        Display();

    }
}

void Game::Display(){
        window->clear();
        window->display();
}