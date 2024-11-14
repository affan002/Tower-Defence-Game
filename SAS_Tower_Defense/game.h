#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "startScreen.h"

class Game{
    private:
        sf::RenderWindow* window;
        std::vector<screen*> screens;
        void Display();
        void manageScreens();
    public:
        Game();
        ~Game();

};