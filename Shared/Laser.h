#pragma once
#include "raylib.h"
#include <iostream>

class Laser{
public:
    Laser(Vector2 position, int speed);
    ~Laser();
    void draw();
    void update();
    void update(int x, int y);
    bool active;
    Rectangle getRect();
public:
    int laserType;
private:
    Vector2 m_position;
    int m_speed;
    int m_width, m_height;
};