#include "enemy.h"

Enemy::Enemy(int _type, std::string _path,std::pair<int,int> pos, int _health, float _speed, float _size, int _wait, int _reward) {
    this->health = _health;
    this->maxHealth = _health;
    this->speed = _speed;
    this->size = _size;
    this->originalSpeed = _speed;

    this->position = Vector2f(pos.first,pos.second);
    SetSprite(_path); 
    InitHealthBar(pos.first,pos.second);
    wait = _wait;
    reward = _reward;
    type = _type;
    this->tile = pos;
}   


void Enemy::SetSprite(std::string _path){
    this->texture.loadFromFile(_path);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2); //origin is at the middle of the tile
    sprite.setScale(Vector2f(size/texture.getSize().x, size/texture.getSize().y));
    this->sprite.setPosition(position);
    
    // sprite.setOrigin(size/2, size/2); //origin is at the middle of the tile
    // std::cout << _path << " " <<std::to_string(static_cast<int>(size/texture.getSize().y)) << std::endl;

}

void Enemy::Render(RenderWindow& window) {
    window.draw(this->sprite);
    window.draw(healthBar);
    window.draw(healthLeft);
    // In the render loop
    window.draw(startText);
}

// void Enemy::Update() {
//     position.x += xVelocity;
//     position.y += yVelocity;
//     distanceTraveled += (abs(xVelocity) + abs(yVelocity));
//     this->sprite.setPosition(position);
//     healthBar.setPosition(position.x-TILELEN/2, position.y-(TILELEN/2));
//     healthLeft.setPosition(position.x-TILELEN/2+3, position.y-(TILELEN/2)+3);
//     healthLeft.setSize(Vector2f((TILELEN - 6)*std::max(health,0)/maxHealth, 4));
//     // health -= 1;
//     // std::cout << " " <<std::to_string(relativePosition.x) << " " <<  std::to_string(relativePosition.y)<< std::endl;

// }

void Enemy::Update() {
    // Call the move function to determine velocities and next position
    move();

    // Check if the enemy has reached the next tile
    // if (abs(position.x - nextTile.first) < abs(xVelocity) && 
    //     abs(position.y - nextTile.second) < abs(yVelocity)) {
    //     position.x = nextTile.first;
    //     position.y = nextTile.second;

    //     // Reset velocity and determine the next move
    //     xVelocity = 0;
    //     yVelocity = 0;
        
        

    //     // Determine the next tile and direction
    //     // CheckDirection();
    // }

    // Update sprite and health bar positions
    this->sprite.setPosition(position);
    healthBar.setPosition(position.x - TILE_SIZE / 2, position.y - TILE_SIZE / 2);
    healthLeft.setPosition(position.x - TILE_SIZE / 2 + 3, position.y - TILE_SIZE / 2 + 3);
    healthLeft.setSize(Vector2f((TILE_SIZE - 6) * std::max(health, 0) / maxHealth, 4));
}





// void Enemy::SetPath(std::map<int ,std::vector<std::pair<int,DIRECTION>>>* _path, int startPos) {
//     this->path = _path;
//     this->tile = startPos;
//     int randTile = std::rand() % ((*path)[tile].size());
//     this->nextTile = (*path)[tile].at(randTile).first;
//     this->dir = (*path)[tile].at(randTile).second;
//     CheckDirection();

// }

// void Enemy::SetPath(std::map<int ,std::vector<std::pair<int,DIRECTION>>>* _path, int startPos,int dist) {
//     this->path = _path;
//     tile = startPos;
//     this->distanceTraveled = dist;
//     int randTile = std::rand() % ((*path)[tile].size());
//     this->nextTile = (*path)[tile].at(randTile).first;
//     this->dir = (*path)[tile].at(randTile).second;
//     CheckDirection();
// }


// void Enemy::UpdatePath() {
//     if (distanceTraveled >= TILELEN) {
//         tile = nextTile;
//         tileNr += 1;
//         int randTile = std::rand() % ((*path)[tile].size());
//         this->nextTile = (*path)[tile].at(randTile).first;
//         this->dir = (*path)[tile].at(randTile).second;
//         distanceTraveled = 0;
//         CheckDirection();
//     }
//     else if (distanceTraveled + (abs(xVelocity) + abs(yVelocity)) >= TILELEN) {
//         xVelocity = (xVelocity == 0) ? 0 : (TILELEN - distanceTraveled) * (xVelocity/abs(xVelocity));
//         yVelocity = (yVelocity == 0) ? 0 : (TILELEN - distanceTraveled) * (yVelocity/abs(yVelocity)); 
//     }
   
// }

// bool Enemy::CheckEndOfPath() {
//     if (tile == (*path)[tile].front().first) {
//         std::cout << "reached end tile" << std::endl;
//         return true;
//     }   
//     return false;
// }


// void Enemy::move(){
    
//     if (levelMap[tile.second/TILELEN][tile.first/TILELEN + 1])
//         this->nextTile = getPos(tile.second/TILELEN,tile.first/TILELEN + 1);
//     // this->distanceTraveled = dist;
//     CheckDirection();
// }



void Enemy::move() {

    std::string s2;
    // Determine current grid position
    int curGridX = position.x / TILE_SIZE;
    int curGridY = position.y / TILE_SIZE;
    
    // if (change){
    //     change = false;
        if (change){
        for (int i = 0; i < 1; i++){
        if (dir == DOWN || dir == UP || dir == IDLE){
        if (levelMap[tile.second/TILELEN][tile.first/TILELEN + 1] == 1){
            if (dir != LEFT){
                dir = RIGHT;
                s2 = "RIGHT";
                break;
            }
        }
        
        if (levelMap[tile.second/TILELEN][tile.first/TILELEN-1] == 1){
            if (dir != RIGHT){
                dir = LEFT;
                s2 = "LEFT";
                break;
            }
        }
        }
        
        if (dir == LEFT || dir == RIGHT || dir == IDLE) {
        if (levelMap[tile.second/TILELEN+1][tile.first/TILELEN] == 1){
            if (dir != UP){
                dir = DOWN;
                s2 = "DOWN";
                break;
            }
        }
        if (levelMap[tile.second/TILELEN-1][tile.first/TILELEN] == 1){
            if (dir != DOWN){
                dir = UP;
                s2 = "UP";
                break;
            }
        }
        }
        //change = false;
        }
        change = false;
        // }
        
    }

    std::string s;
    // Determine the next grid position based on direction
    switch (dir) {
        
        case RIGHT:
            if (levelMap[curGridY][curGridX + 1] == 1  ) {
                nextTile = getPos(curGridY, curGridX + 1);
                this->sprite.setRotation(90);
                s = "RIGHT";
            }
            break;
        case LEFT:
            if (levelMap[curGridY][curGridX - 1] == 1 ) {
                nextTile = getPos(curGridY, curGridX - 1);
                this->sprite.setRotation(270);
                s = "LEFT";
            }
            break;
        case UP:
            if (levelMap[curGridY - 1][curGridX] == 1 ) {
                nextTile = getPos(curGridY - 1, curGridX);
                this->sprite.setRotation(0);
               s = "UP"; 
            }
            
            break;
        case DOWN:
            if (levelMap[curGridY + 1][curGridX] == 1 ) {
                nextTile = getPos(curGridY + 1, curGridX);
                this->sprite.setRotation(180);
                s = "DOWN";
            }
            break;
        case IDLE:
            // No movement
            return;
    }

    

    // Calculate velocity to move towards the next tile
    double m = sqrt(pow(nextTile.first-position.x,2) + pow(nextTile.second - position.y, 2));
    // speed = 0.5;
    xVelocity = (nextTile.first - position.x) * speed / m;
    yVelocity = (nextTile.second - position.y) * speed / m;

        this->startFont.loadFromFile("fonts/upheavtt.ttf");
        this->startText.setFont(this->startFont);
        this->startText.setString(s + "   "  +std::to_string(tile.first) + "   " + std::to_string(tile.second) + "    " + std::to_string(position.x) + "    "  + std::to_string(position.y));
        this->startText.setFillColor(Color::Black);
        this->startText.setCharacterSize(20);
        this->startText.setPosition(20,20);
    
    // Update the position based on calculated velocity
    position.x += xVelocity;
    position.y += yVelocity;


    int curGridXNew = position.x / TILE_SIZE;
    int curGridYNew = position.y / TILE_SIZE;
    
    if (curGridX != curGridXNew || curGridY != curGridYNew){
        tile = nextTile;
        change = true;
    }
    

    // this->tile = nextTile;
    // Check if the enemy has reached the next tile
    // if (abs(position.x - nextTile.first) < abs(xVelocity) && 
    //     abs(position.y - nextTile.second) < abs(yVelocity)) {
    //     // Snap to the next tile
    //     position.x = nextTile.first;
    //     position.y = nextTile.second;

    //     // Update the tile to reflect the grid position
    //     tile = std::make_pair(nextTile.second / TILE_SIZE, nextTile.first / TILE_SIZE);
    // }
}



// void Enemy::move() {
//     int curGridX = position.x / TILE_SIZE;
//     int curGridY = position.y / TILE_SIZE;

//     // Update direction based on level map
//     if (change) {
//         if (levelMap[tile.second / TILELEN][tile.first / TILELEN + 1] == 1 && dir != LEFT) {
//             dir = RIGHT;
//             change = false;
//         } else if (levelMap[tile.second / TILELEN][tile.first / TILELEN - 1] == 1 && dir != RIGHT) {
//             dir = LEFT;
//             change = false;
//         }  else if (levelMap[tile.second / TILELEN + 1][tile.first / TILELEN] == 1 && dir != UP) {
//             dir = DOWN;
//             change = false;
//         } else if (levelMap[tile.second / TILELEN - 1][tile.first / TILELEN] == 1 && dir != DOWN) {
//             dir = UP;
//             change = false;
//         }
//     }

//     // Calculate next tile and velocity
//     switch (dir) {
//         case RIGHT:
//             nextTile = getPos(curGridY, curGridX + 1);
//             sprite.setRotation(90);
//             break;
//         case LEFT:
//             nextTile = getPos(curGridY, curGridX - 1);
//             sprite.setRotation(270);
//             break;
//         case UP:
//             nextTile = getPos(curGridY - 1, curGridX);
//             sprite.setRotation(0);
//             break;
//         case DOWN:
//             nextTile = getPos(curGridY + 1, curGridX);
//             sprite.setRotation(180);
//             break;
//         case IDLE:
//             return;
//     }

//     // Calculate velocity
//     float dx = nextTile.first - position.x;
//     float dy = nextTile.second - position.y;
//     float distance = sqrt(dx * dx + dy * dy);
//     xVelocity = (dx / distance) * speed;
//     yVelocity = (dy / distance) * speed;

//     // Update position
//     position.x += xVelocity;
//     position.y += yVelocity;

//     // Snap to next tile if close enough
//     if (fabs(position.x - nextTile.first) < 0.5f && fabs(position.y - nextTile.second) < 0.5f) {
//         position = { static_cast<float>(nextTile.first), static_cast<float>(nextTile.second) };

//         tile = nextTile;
//         change = true;
//     }
// }







void Enemy::InitHealthBar(float x, float y) {
    healthBar.setPosition(position.x-TILELEN/2, position.y-(TILELEN/2));
    healthLeft.setPosition(position.x-TILELEN/2+3, position.y-(TILELEN/2)+3);
    healthBar.setSize(Vector2f(TILELEN, 10));
    healthLeft.setSize(Vector2f(TILELEN - 6, 4));
    healthBar.setFillColor(sf::Color(0x2b2b2bff));
    healthLeft.setFillColor(Color::Red);
}

void Enemy::CheckDirection() {
    // switch (dir) {
    //     case UP:
    //         yVelocity = 0-speed;
    //         xVelocity = 0;
    //         break;
    //     case DOWN:
    //         yVelocity = speed;
    //         xVelocity = 0;
    //         break;
    //     case LEFT:
    //         xVelocity = 0-speed;
    //         yVelocity = 0;
    //         break;
    //     case RIGHT:
    //         xVelocity = speed;
    //         yVelocity = 0;
    //         break;
    //     case IDLE:
    //         xVelocity = 0;
    //         yVelocity = 0;
    //         break;
    //     }
    
}

int Enemy::GetWait(){
    return wait;
}
Enemy::~Enemy(){
    
}

sf::Sprite Enemy::GetSprite(){
    return this->sprite;
}

bool Enemy::CheckIfDead(){
    return (health <= 0);
}

int Enemy::GetTileNr() {
   return tileNr;
}

void Enemy::GetHit(int damage){
   this->health =this->health- damage;
}

int Enemy::GetReward() {
    return reward;
}

void Enemy::setSpeed(float newSpeed){
    this->speed = newSpeed;
}

float Enemy::getOriginalSpeed(){
    return this->originalSpeed;
}

const int Enemy::GetType() {
    return type;
}

sf::Vector2f Enemy::GetPosition(){
    return sf::Vector2f(position.x - (TILELEN/2), position.y - (TILELEN/2)) ;
}
std::pair<int,int> Enemy::GetCurTile() {
    return tile;
}
int Enemy::GetDist(){
    return distanceTraveled;
}

