#include "Prowler.h"

Prowler::Prowler(Vector2 position)
{
    setTexture();
    m_position = position;
    m_speed = 3;
    m_laser_speed = 2;
    m_fireRate = 0.5;
}

void Prowler::setTexture()
{
    m_image=LoadTexture("../Resources/alien_1.png");
}
