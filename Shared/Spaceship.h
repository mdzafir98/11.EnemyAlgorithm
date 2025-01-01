#pragma once
#include <vector>
#include "Laser.h"

class Spaceship{
public:
    Spaceship();
    ~Spaceship();
    void draw();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void fireLaser();
    void drawStats();
    void getDamaged(int damage);
    Vector2 getPosition();
    Rectangle getRect();
private:
    Texture2D image;
    Vector2 m_position;
    double lastFireTime;
    float m_speed;
    int m_health{10};
public:
    std::vector<Laser> lasers;
    float fireRate{0.35};
    int laserDamage;
    bool alive;
};