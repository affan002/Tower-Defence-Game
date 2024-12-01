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

Enemy::Enemy(int _type, std::string _path,std::pair<int,int> pos, int _health, float _speed, float _size, int _wait, int _reward, int _dir) {
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
    this->dir = _dir;
    switch (dir) {
        case RIGHT:
            sprite.setRotation(90);
            break;
        case LEFT:
            sprite.setRotation(270);
            break;
        case UP:
            sprite.setRotation(0);
            break;
        case DOWN:
            sprite.setRotation(180);
            break;
        
    }
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

}

void Enemy::Update() {
    // Call the move function to determine velocities and next position
    move();

    
    // Update sprite and health bar positions
    sf::Vector2f spritePos(position.x+20,position.y+20);
    this->sprite.setPosition(spritePos);
    healthBar.setPosition(spritePos.x - TILE_SIZE / 2, spritePos.y - TILE_SIZE / 2);
    healthLeft.setPosition(spritePos.x - TILE_SIZE / 2 + 3, spritePos.y - TILE_SIZE / 2 + 3);
    healthLeft.setSize(Vector2f((TILE_SIZE - 6) * std::max(health, 0) / maxHealth, 4));
}


void Enemy::move() {
    std::string s;
    // Determine current grid position
    int curGridX = position.x / TILE_SIZE;
    int curGridY = position.y / TILE_SIZE;

    // If the direction needs to change, handle the update
    if (change) {
        
        if (dir == UP || dir == DOWN || dir == IDLE) {
            if (levelMap[tile.second / TILELEN][tile.first / TILELEN + 1] == 1) {
                dir = RIGHT;
                sprite.setRotation(90);
                change = false;  // No need to change direction again until next cycle
            } else if (levelMap[tile.second / TILELEN][tile.first / TILELEN - 1] == 1) {
                
                dir = LEFT;
                sprite.setRotation(270);
                change = false;
            }
            
            // break;
        }

        else if (dir == LEFT || dir == RIGHT || dir == IDLE) {
                
            if (levelMap[tile.second / TILELEN + 1][tile.first / TILELEN] == 1) {
                dir = DOWN;
                sprite.setRotation(180);
                change = false;
            } else if (levelMap[tile.second / TILELEN - 1][tile.first / TILELEN] == 1) {
                dir = UP;
                sprite.setRotation(0);
                change = false;
            }

        }    
    }
    // Handle movement in the new direction
    
    switch (dir) {
        case RIGHT:
            if (levelMap[curGridY][curGridX + 1] == 1) {
                
                nextTile = getPos(curGridY, curGridX + 1);
                s = "RIGHT";
            }
            break;
        case LEFT:
            if (levelMap[curGridY][curGridX - 1] == 1) {
                
                nextTile = getPos(curGridY, curGridX - 1);
                s = "LEFT";
            }
            break;
        case UP:
            if (levelMap[curGridY - 1][curGridX] == 1) {
                
                nextTile = getPos(curGridY - 1, curGridX);
                s = "UP";
            }
            break;
        case DOWN:
            if (levelMap[curGridY + 1][curGridX] == 1) {
                
                nextTile = getPos(curGridY + 1, curGridX);
                s = "DOWN";
            }
            break;
        case IDLE:
            s = "IDLE";
            break; // No movement
        default:
            s = "DEFAULT";
            break;
    }

    // Calculate velocity to move towards the next tile
    float dx = nextTile.first - position.x;
    float dy = nextTile.second - position.y;
    float distance = sqrt(dx * dx + dy * dy);
    xVelocity = (dx / distance) * speed;
    yVelocity = (dy / distance) * speed;

    // Update position based on velocity
    position.x += xVelocity;
    position.y += yVelocity;
    

    // After moving, check if the position has reached the target grid cell
    if (fabs(position.x - nextTile.first) < 1.0f && fabs(position.y - nextTile.second) < 1.0f) {
        // Snap to grid to avoid floating-point drift
        position.x = nextTile.first;
        position.y = nextTile.second;
        change = true;  // Allow direction change for the next move
    }
    // After moving, check if the position has passed the grid boundary
    int curGridXNew = position.x / TILE_SIZE;
    int curGridYNew = position.y / TILE_SIZE;

    if (curGridX != curGridXNew || curGridY != curGridYNew) {
        
        tile = nextTile;
        change = true;  // Mark for next direction update
    }


}


void Enemy::InitHealthBar(float x, float y) {
    healthBar.setPosition(position.x-TILELEN/2, position.y-(TILELEN/2));
    healthLeft.setPosition(position.x-TILELEN/2+3, position.y-(TILELEN/2)+3);
    healthBar.setSize(Vector2f(TILELEN, 10));
    healthLeft.setSize(Vector2f(TILELEN - 6, 4));
    healthBar.setFillColor(sf::Color(0x2b2b2bff));
    healthLeft.setFillColor(Color::Red);
}

void Enemy::setDir(int dir){
    this->dir = dir;
}

int Enemy::getDir(){
    return this->dir;
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
void Enemy::SetFrozenEffect(){
    sprite.setColor(sf::Color(0,191,255));
}

void Enemy::RemoveFrozenEffect(){
    sprite.setColor(sf::Color(255,255,255));
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

