#ifndef MILL_TOWER_HPP
#define MILL_TOWER_HPP

#include "tower.h"
#include "bullet.h"
#include "enemy.h"
#include "player.h"

class millTower: public Tower
{
private:
    sf::Texture texture;
    sf::Sprite sprite;


    float wait = 0;

    Player *player;   

public:
    millTower(std::string _path, sf::Vector2f pos, sf::Vector2f resize, Player *player);
    ~millTower();


    void Update(const sf::Vector2f mousePos, const float& dt);
    void Render(sf::RenderTarget* window);
    void rotate(sf::Vector2i mousePos, sf::Vector2f pos);
    void enemieInRange(std::vector<Enemy*> enemies);

    void collisionDetect(std::vector<Enemy*> enemies, float dt);
    
};


#endif