#include "tower.h"


bool Tower::inRange(sf::Vector2f enemyPos, sf::CircleShape range){
    double distx = pow(enemyPos.x-range.getPosition().x,2);
    double disty = pow(enemyPos.y-range.getPosition().y,2);
    double dist = sqrt(distx+disty);


    if(dist <= range.getRadius()){
        return true;
    }
    else{
        return false;
    }
}

