#pragma once
#include "../Shared/Spaceship.h"
#include "../Shared/Timer.h"
#include "../Shared/Enemy.h"
#include "../Shared/Prowler.h"
#include <math.h>

class Game{
public:
    Game();
    ~Game();
    void initGame();
    void draw();
    void update();
    void handleInput();
    void handleFireLaser();
    void drawText();
    void drawInterface();
    void initEnemies();
    void handleEnemies();
    void checkCollisions();
public:
    Spaceship spaceship;
    Enemy* alien;
    Prowler* prowler;
private:
    void deleteInactiveLaser();
    bool alive;
    Vector2 laserVector;
private:
    double lastTime{0};
    int fireRateToken{3};
    Timer fireRateTimer{0};
    float firerateLife{2.0f};
private:
    std::vector<Enemy*> enemies;
    Vector2 mousePos;
};