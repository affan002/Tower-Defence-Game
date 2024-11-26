#ifndef TD_WAVE_HPP
#define TD_WAVE_HPP

#include "Enemy.h"
#include <vector>

class Wave
{
private:
    int waveNumber;         // The current wave number
    int enemyCount;         // Number of enemies in the current wave
    int spawnDelay;         // Delay between enemy spawns (frames)
    int timeSinceLastSpawn; // Timer to manage spawn delay
    int rewardPerEnemy;     // Reward per enemy

public:
    std::vector<Enemy *> enemies; // List of enemies in the wave
    Wave(int waveNum, int numEnemies, int delay, int reward);
    ~Wave();

    void Update();                                                                         // Update logic for spawning and enemy movement
    void Render(RenderWindow &window);                                                     // Render all enemies in the wave
    void SpawnEnemy(std::pair<int, int> startPosition, int type, std::string texturePath); // Spawn a new enemy

    bool IsWaveComplete();     // Check if all enemies in the wave have been defeated
    int GetRemainingEnemies(); // Get the number of remaining enemies
    int GetWaveReward();       // Get the total reward for the wave
};

#endif
