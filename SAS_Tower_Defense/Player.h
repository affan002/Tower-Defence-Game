#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>



class Player
{
    private:
        sf::Font font;
        sf::Text healthText;
        sf::Text coinsText;
        // enemies
        
    public:
        int health = 10;
        int coins = 500;
        Player();
        void Update();
        void draw(sf::RenderWindow& window);
};