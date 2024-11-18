#ifndef ENEMY
#define ENEMY

#include <SFML/Graphics.hpp>

class Enemy {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
public:
    virtual void Update() = 0;
    virtual void move() = 0;
    virtual void Render(sf::RenderWindow*) = 0;
    virtual void findNextPosition() = 0;
};

#endif

