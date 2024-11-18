#ifndef TANKENEMY
#define TANKENEMY

#include "Enemy.h"


class TankEnemy : public Enemy {
public:
    TankEnemy();
    void move();
    void Update();
    void Render(sf::RenderWindow* window);

private:
    std::vector<std::vector<int>> path;
    int currentX;
    int currentY;
    void findNextPosition();
};

#endif // TANKENEMY_H