#ifndef TD_ENEMY_HPP
#define TD_ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
// #include <list>
#include <stdlib.h> 
#include <sstream>
#include "Map.h"

int TILELEN = TILE_SIZE;

using namespace sf;

class Enemy {
    private:
        enum DIRECTION{UP, RIGHT , DOWN, LEFT, IDLE};
        Texture texture;
        Sprite sprite;
        Vector2f position;

        
        int maxHealth;
        RectangleShape healthBar;
        RectangleShape healthLeft;    

        float yVelocity = 0;
        float xVelocity = 0;
        float distanceTraveled = 0;
        float speed;
        float originalSpeed;

        // std::map<int ,std::vector<std::pair<int,DIRECTION>>> *path;
        std::pair<int,int> tile; 
        int tileNr = 0;
        std::pair<int,int> nextTile;
        int dir = IDLE;
        bool change = true;
        
        // std::vector<std::pair<int,int>> visited;

        float size;
        int wait;
        int reward;
        int type;


        
    public:
        int health;
        Enemy(int _type, std::string _path, std::pair<int,int>, int _health, float _speed, float _size, int _wait, int _reward);
        Enemy(int _type, std::string _path, std::pair<int,int>, int _health, float _speed, float _size, int _wait, int _reward, int dir);
        ~Enemy();
        void Update();
        void Render(RenderWindow &window);
        void SetSprite(std::string path);
        Sprite GetSprite();

        void move();
        bool CheckIfDead();
        void GetHit(int damage);
        void InitHealthBar(float, float);
        int GetWait();
        int GetTileNr(); //see how far the enemy has gone
        int GetReward();

        // for debugging
        int getHealth(){return health;}

        void setDir(int dir);
        int getDir();
        // for freeze_tower
        float getOriginalSpeed();
        void setSpeed(float newSpeed);
        void SetFrozenEffect();
        void RemoveFrozenEffect();
        const int GetType();
        sf::Vector2f GetPosition();
        std::pair<int,int> GetCurTile();
        std::pair<int,int> GetNextTile();
        int GetDist();
};


#endif 