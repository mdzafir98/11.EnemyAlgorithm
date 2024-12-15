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
    Vector2 getPosition();
    Rectangle getRect();
private:
    Texture2D image;
    Vector2 m_position;
    double lastFireTime;
    int m_speed;
public:
    std::vector<Laser> lasers;
    float fireRate{0.35};
};