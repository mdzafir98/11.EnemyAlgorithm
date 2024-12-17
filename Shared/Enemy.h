#pragma once
#include <vector>
#include "Laser.h"

class Enemy{
public:
    Enemy();
    Enemy(Vector2 position, float speed, int laser_speed, float fireRate);
    ~Enemy();
    void draw();
    virtual void update();
    void mouseClicked();
    virtual void setTexture();
    void showStats();
    void drawStats();
public:
    void getDamaged(int damage);
    virtual void fireLaser();
    virtual void moveLeft();
    virtual void moveRight();
    virtual void moveDown();
    virtual void moveUp();
    Vector2 getPos();
    void setPos(Vector2 position);
    Rectangle getRect();
public:
    Texture2D m_image;
    Vector2 m_position;
    int m_type{0};
    float m_speed;
    int m_laser_speed;
    float m_fireRate;
    double lastFireTime;
    bool alive{true};
    bool clicked{false};
    int m_health{5};
public:
    std::vector<Laser> lasers;
    void drawEnemyLaser();
    void updateLaser();
    void deleteLaser();
};