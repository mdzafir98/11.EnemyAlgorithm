#include "Spaceship.h"

Spaceship::Spaceship(){
    image=LoadTexture("../Resources/player.png");
    m_position.x=(GetScreenWidth()-image.width)/2;
    m_position.y=GetScreenHeight()-image.height;
    lastFireTime = 0;
    m_speed = 7;
    laserDamage = 1;
}

Spaceship::~Spaceship(){
    UnloadTexture(image);
}

void Spaceship::draw(){
    DrawTextureV(image,m_position,WHITE);
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

Vector2 Spaceship::getPosition(){
    return m_position;
}

Rectangle Spaceship::getRect()
{
    return {m_position.x, m_position.y, (float)image.width, (float)image.height};
}

