#include "Spaceship.h"

Spaceship::Spaceship(){
    image=LoadTexture("../Resources/player.png");
    m_position.x=(GetScreenWidth()-image.width)/2;
    m_position.y=GetScreenHeight()-image.height;
    lastFireTime = 0;
    m_speed = 7.f;
    laserDamage = 1;
    alive = true;
}

Spaceship::~Spaceship(){
    UnloadTexture(image);
    std::cout << "spaceship entity destroyed!" << "\n";
}

void Spaceship::draw(){
    DrawTextureV(image,m_position,WHITE);
    // drawStats();
}

void Spaceship::moveLeft(){
    m_position.x-=m_speed;
    if (m_position.x<0){
        m_position.x=0;
    }
}

void Spaceship::moveRight(){
    m_position.x+=m_speed;
    if (m_position.x + image.width>GetScreenWidth()){
        m_position.x=GetScreenWidth() - image.width;
    }
}

void Spaceship::moveUp(){
    m_position.y-=m_speed;
    if (m_position.y<0){
        m_position.y=0;
    }
}

void Spaceship::moveDown(){
    m_position.y+=m_speed;
    if (m_position.y + image.height>GetScreenHeight()){
        m_position.y=GetScreenHeight() - image.height;
    }
}

void Spaceship::fireLaser(){
    if (GetTime()-lastFireTime>=fireRate){
        lasers.push_back(Laser({m_position.x+image.width/2-2, m_position.y},-6));
        lastFireTime=GetTime();
    }
}

void Spaceship::drawStats()
{
    DrawText(TextFormat("SPD: %.2f", m_speed),m_position.x, m_position.y-10, 8, {255,255,255,200});
    DrawText(TextFormat("FR: %.2f", fireRate),m_position.x, m_position.y-20, 8, {255,255,255,200});
    DrawText(TextFormat("HP: %i", m_health),m_position.x, m_position.y-30, 8, {255,255,255,200});
}

void Spaceship::getDamaged(int damage)
{
    if (m_health > 0){
        m_health -= damage;
    } else{
        m_health = 0;
    }
}

Vector2 Spaceship::getPosition(){
    return m_position;
}

Rectangle Spaceship::getRect()
{
    return {m_position.x, m_position.y, (float)image.width, (float)image.height};
}

