#include "milltower.h"

MillTower::MillTower(std::string _path, sf::Vector2f pos, sf::Vector2f resize, Player *player):Tower()
{
    this->texture.loadFromFile(_path);
    this->sprite.setTexture(texture);
    this->sprite.scale(resize);
    this->sprite.setOrigin(this->texture.getSize().x/2,this->texture.getSize().y/2 );
    this->sprite.setPosition(pos.x+24,pos.y+24);


    this->range.setRadius(150);
    this->range.setOrigin(this->range.getRadius(),this->range.getRadius());
    this->range.setPosition(pos.x+24,pos.y+24);

    this->isSomeEmemy = false;
    this->player=player;
    
}

MillTower::~MillTower()
{
}


void MillTower::Update(const sf::Vector2f mousePos, const float& dt){
    wait += 1;

    if(wait >= 1000){
       this->player->coins+=50;
       this->wait=0;
    }
}

void MillTower::Render(sf::RenderTarget* window){
    window->draw(sprite);
}

void MillTower::rotate(sf::Vector2i mousePos, sf::Vector2f pos){

}

void MillTower::enemieInRange(std::vector<Enemy*> enemies){

}


void MillTower::collisionDetect(std::vector<Enemy*> enemies, float dt){
}