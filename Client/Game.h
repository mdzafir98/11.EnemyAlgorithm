#pragma once
#include "../Shared/Spaceship.h"
#include "../Shared/Timer.h"
#include "../Shared/Enemy.h"
#include "../Shared/Prowler.h"
#include "../Shared/Mothership.h"
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
    void checkEnemyHealth();
    void checkCollisions();
    void changeType();
    void deleteInactiveLaser();
public:
    Spaceship spaceship;
    Enemy* alien;
    Prowler* prowler;
    Mothership* mothership;
private:
    bool alive;
    Vector2 laserVector;
private:
    double lastTime{0};
    int fireRateToken{3};
    Timer fireRateTimer{0};
    float firerateLife{2.0f};
    std::vector<Enemy*> enemies;
    Vector2 mousePos;
    int enemyType{0};
};