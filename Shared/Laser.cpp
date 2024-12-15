#include "Laser.h"

Laser::Laser(Vector2 position, int speed){
    m_position=position;
    m_speed=speed;
    m_width=4;
    m_height=15;
    active=true;
}

Laser::~Laser()
{
}

void Laser::draw(){
    if (active){
        DrawRectangle(m_position.x,m_position.y,4,4,{243,216,53,255});
    }
}

void Laser::update(){
    m_position.y+=m_speed;
    if (active){
        if(m_position.y>GetScreenHeight() || m_position.y<0){
            active=false;
        }
    }
}

void Laser::update(int x, int y){
    m_position.x+=x;
    m_position.y+=y;
}

Rectangle Laser::getRect(){
    return {m_position.x,m_position.y,m_width,m_height};
}
