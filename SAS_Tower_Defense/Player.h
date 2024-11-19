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
        Player(){
            {
    this->font.loadFromFile("fonts/upheavtt.ttf");
    this->healthText.setFont(this->font);
    this->healthText.setFillColor(sf::Color::Black);
    this->healthText.setCharacterSize(30);
    

    this->coinsText.setFont(this->font);
    this->coinsText.setFillColor(sf::Color::Black);
    this->coinsText.setCharacterSize(30);


    healthText.setString("Health: " + std::to_string(health));
    coinsText.setString("Coins: " + std::to_string(coins));
    this->coinsText.setPosition(1000,5);
    this->healthText.setPosition(1000,40);
}
        }
        void Update(){
            healthText.setString("Health: " + std::to_string(health));
    coinsText.setString("Coins: " + std::to_string(coins));
        }
        void draw(sf::RenderWindow& window){
            window.draw(this->healthText);
    window.draw(this->coinsText);
        }
};