#ifndef GUN_TOWER_H
#define GUN_TOWER_H

#include "tower.h"
#include "bullet.cpp"
#include "enemy.h"

class GunTower: public Tower
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

   
    sf::CircleShape range;

    sf::Vector2f targetEmeny;
    bool isSomeEmemy;

    Bullet *bullet;

    float wait = 0;

    bool isHit = false;   
        sf::Text debugText;
        sf::Font debugfont;

public:
    GunTower(std::string _path, sf::Vector2f pos, sf::Vector2f resize);
    ~GunTower();


    void Update(const sf::Vector2f mousePos);
    void Render(sf::RenderTarget* window);
    void rotate(sf::Vector2i mousePos, sf::Vector2f pos);
    void enemieInRange(std::vector<Enemy*> enemies);

    void collisionDetect(std::vector<Enemy*> enemies);
};









#endif