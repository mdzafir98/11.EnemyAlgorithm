#pragma once
#include "Enemy.h"
#include <cmath>

class Prowler : public Enemy{
public:
    Prowler(Vector2 position);
    virtual void update() override;
    void setTexture();
    bool checkArea(Vector2 playerPos);
    float pyDistance(Vector2 enemyPos, Vector2 playerPos);
    void chasePlayer();
public:
    bool nearPlayer{false};
};
