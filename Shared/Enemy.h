#pragma once
#include <vector>
#include "Laser.h"
#include "../DesignPattern/Visitor.h"

class Enemy{
public: //functions
    Enemy();
    Enemy(Vector2 position, float speed, int laser_speed, float fireRate);
    virtual ~Enemy();
    void draw();
    virtual void update();
    void mouseClicked();
    virtual void setTexture();
    void showStats();
    void drawStats();
    void getDamaged(int damage);
    virtual void fireLaser();
    virtual void moveLeft();
    virtual void moveRight();
    virtual void moveDown();
    virtual void moveUp();
    virtual void behave(Vector2 playerPos);
    void drawEnemyLaser();
    void updateLaser();
    void deleteLaser();
    Vector2 getPos();
    void setPos(Vector2 position);
    Rectangle getRect();
    virtual void accept(Visitor* visitor);
public: //variables
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
    std::vector<Laser> lasers;
};