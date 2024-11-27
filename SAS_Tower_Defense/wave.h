#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
// #include "enemy.h"
#include "enemy.cpp"
#include "Player.h"
#include <iostream>

// int MAPDIM = 15;

class Wave
{
private:

    std::string name;
    std::pair<int, int> startPos;
    Font font;
    Text text;
    // enemies
    std::vector<Enemy *> enemiesWaitlist;
    std::vector<Enemy *> enemies;
    sf::Clock spawnClock;
    float wait = 2;
    Player *player;
    // std::map<int, std::vector<std::pair<int, DIRECTION>>> *path;

public:
    Wave(std::string _name, int e1, int e2, int e3, int e4, int e5, std::pair<int, int>, Player*); // number of enemies from each type
    ~Wave();

    void Update();
    void Render(sf::RenderWindow& window);
    // void SetPath(std::map<int, std::vector<std::pair<int, DIRECTION>>> *_path);
    bool HasEnded();

    std::vector<Enemy *> getCurEnemies();
};