#ifndef TOWERS_H
#define TOWERS_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <cmath>
#include "enemy.h"


class Tower
{
    
public:
    Tower()=default;
    ~Tower()=default;

    virtual void Update(const sf::Vector2f mousePos)=0;
    virtual void Render(sf::RenderTarget* window)=0;

    virtual void rotate(sf::Vector2i mousePos, sf::Vector2f pos)=0;
    bool inRange(sf::Vector2f mousePos, sf::CircleShape range);

    virtual void enemieInRange(std::vector<Enemy*> enemies)=0;
    virtual void collisionDetect(std::vector<Enemy*> enemies)=0;
};




#endif