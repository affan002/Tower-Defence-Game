#ifndef CONST_H
#define CONST_H

// Screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 600;

// Directions
enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    IDLE
};

// Other game constants
const float ENEMY_SPEED = 1.0f;
const int ENEMY_HEALTH = 100;
const float ENEMY_SIZE = 1.0f;
const int ENEMY_WAIT = 0;
const int ENEMY_REWARD = 10;

#endif // CONST_H