#include "SlowDownTower.h"

SlowDownTower::SlowDownTower(std::string _path, sf::Vector2f pos, sf::Vector2f resize):Tower()
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
    
}

SlowDownTower::~SlowDownTower()
{
}


void SlowDownTower::Update(const sf::Vector2f mousePos){
    
    // bullet animation
    if(this->range.getGlobalBounds().contains(mousePos)){
        this->range.setFillColor(sf::Color(178,178,178,100));
    }
    else{
        this->range.setFillColor(sf::Color(178,178,178,0));
    }

    if(this->isSomeEmemy){
        this->rotate(sf::Vector2i(this->targetEmeny.x,this->targetEmeny.y), this->targetEmeny);;
    }
}

void SlowDownTower::Render(sf::RenderTarget* window){
    window->draw(range);
    window->draw(sprite);
}

void SlowDownTower::rotate(sf::Vector2i mousePos, sf::Vector2f pos){
    double dx = this->sprite.getPosition().x - mousePos.x;
    double dy = this->sprite.getPosition().y - mousePos.y;
    
    if(this->inRange(pos, this->range)){
        this->sprite.setRotation(180+((atan2(dy, dx)) * 180 / M_PI));
    }
}

void SlowDownTower::enemieInRange(std::vector<Enemy*> enemies){
    
    this->isSomeEmemy = false;
    for(auto i: enemies){
        if(this->inRange(i->GetSprite().getPosition(), range)){
            this->targetEmeny = i->GetSprite().getPosition();
            this->isSomeEmemy = true;
            i->setSpeed((i->getOriginalSpeed())*0.5);
            i->SetFrozenEffect();
        }
        else{
            i->setSpeed(i->getOriginalSpeed());
            i->RemoveFrozenEffect();
        }
           
    }    
}


void SlowDownTower::collisionDetect(std::vector<Enemy*> enemies){
}