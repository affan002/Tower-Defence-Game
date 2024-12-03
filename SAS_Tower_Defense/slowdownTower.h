#ifndef SlowDownTower_H
#define SlowDownTower_H


#include "tower.h"
#include "bullet.h"
#include "enemy.h"


class SlowDownTower: public Tower
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

   
    sf::CircleShape range;

    sf::Vector2f targetEmeny;
    bool isSomeEmemy;


    float wait = 0;

    bool isHit = false;
    // slows down enemy 
    float speedMulti = 0.1;   

public:
    SlowDownTower(std::string _path, sf::Vector2f pos, sf::Vector2f resize);
    ~SlowDownTower();


    void Update(const sf::Vector2f mousePos);
    void Render(sf::RenderTarget* window);
    void rotate(sf::Vector2i mousePos, sf::Vector2f pos);
    void enemieInRange(std::vector<Enemy*> enemies);

    void collisionDetect(std::vector<Enemy*> enemies);
};




#endif