#include "Wave.h"

Wave::Wave(int waveNum, int numEnemies, int delay, int reward)
    : waveNumber(waveNum), enemyCount(numEnemies), spawnDelay(delay), timeSinceLastSpawn(0), rewardPerEnemy(reward) {}

Wave::~Wave()
{
    // Cleanup: delete all enemy instances
    for (auto enemy : enemies)
    {
        delete enemy;
    }
}

void Wave::Update()
{
    // If enough time has passed, spawn a new enemy
    if (timeSinceLastSpawn >= spawnDelay && enemies.size() < enemyCount)
    {
        SpawnEnemy({2, 0}, 1, "images/ship1.png"); // Customize this to choose start positions and textures
        timeSinceLastSpawn = 0;                             // Reset the spawn timer
    }

    // Update each enemy in the wave
    for (auto enemy : enemies)
    {
        enemy->Update();
    }

    // Increment the spawn timer
    timeSinceLastSpawn++; // This should increment each frame
}

void Wave::Render(RenderWindow &window)
{
    // Render each enemy in the wave
    for (auto enemy : enemies)
    {
        enemy->Render(window);
    }
}

void Wave::SpawnEnemy(std::pair<int, int> startPosition, int type, std::string texturePath)
{
    // Create a new enemy and add it to the wave
    Enemy *newEnemy = new Enemy(type, texturePath, startPosition, 100, 1.0f, 50.f, 0, rewardPerEnemy);
    enemies.push_back(newEnemy);
}

bool Wave::IsWaveComplete()
{
    // Check if all enemies are dead
    for (auto enemy : enemies)
    {
        if (!enemy->CheckIfDead())
        {
            return false; // At least one enemy is still alive
        }
    }
    return true; // All enemies are dead
}

int Wave::GetRemainingEnemies()
{
    int remaining = 0;
    for (auto enemy : enemies)
    {
        if (!enemy->CheckIfDead())
        {
            remaining++;
        }
    }
    return remaining;
}

int Wave::GetWaveReward()
{
    int totalReward = 0;
    for (auto enemy : enemies)
    {
        if (enemy->CheckIfDead())
        {
            totalReward += enemy->GetReward();
        }
    }
    return totalReward;
}
