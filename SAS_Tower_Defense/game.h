#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

class Game{
    private:
        sf::RenderWindow* window;
        std::vector<Enemy*> enemies;

    public:
        Game();
        ~Game();
        void Run();
        void Update();
        void Display();
        void Render();
};