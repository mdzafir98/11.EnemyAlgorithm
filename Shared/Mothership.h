#pragma once
#include "Enemy.h"
#include <vector>
#include <cmath>

class Mothership : public Enemy{
public:
    Mothership(Vector2 position);
    ~Mothership();
    void update() override;
    void setTexture();
    void behave(Vector2 playerPos) override;
    float pyDistance(Vector2 enemyPos, Vector2 playerPos);
    void spawnEnemy();
public:
    bool nearPlayer{false};
    bool wallFlag{false};
    int spawnCount{3};
    double lastSpawnTime;
    float spawnRate{2.f};
    std::vector<Enemy*> enemies;
private:
    bool checkArea(Vector2 playerPos);
};