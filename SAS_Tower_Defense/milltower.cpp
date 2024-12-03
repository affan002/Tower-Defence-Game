#include "milltower.h"

millTower::millTower(std::string _path, sf::Vector2f pos, sf::Vector2f resize, Player *player)
{
    this->texture.loadFromFile(_path);
    this->sprite.setTexture(texture);
    this->sprite.scale(resize);
    this->sprite.setOrigin(this->texture.getSize().x/2,this->texture.getSize().y/2);
    this->sprite.setPosition(pos.x+24,pos.y+24);

    this->player = player;
}

millTower::~millTower()
{
}

void millTower::Update(const sf::Vector2f mousePos, const float& dt)
{
    wait += dt;

    if(wait >= 10){
       this->player->coins+=50;
       this->wait=0;
    }
}

void millTower::Render(sf::RenderTarget* window)
{
    window->draw(sprite);
}

void millTower::rotate(sf::Vector2i mousePos, sf::Vector2f pos)
{
}

void millTower::enemieInRange(std::vector<Enemy*> enemies)
{
}

void millTower::collisionDetect(std::vector<Enemy*> enemies, float dt)
{
}

