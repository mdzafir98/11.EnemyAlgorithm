#pragma once
#include "Enemy.h"
#include <cmath>

class Prowler : public Enemy{
public:
    Prowler(Vector2 position);
    ~Prowler() override;
    void update() override;
    void behave(Vector2 playerPos) override;
    void setTexture();
    float pyDistance(Vector2 enemyPos, Vector2 playerPos);
    void accept(Visitor* visitor) override;
public:
    bool nearPlayer{false};
private:
    void chasePlayer();
    bool checkArea(Vector2 playerPos);
};
