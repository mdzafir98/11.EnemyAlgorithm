#include "Prowler.h"

Prowler::Prowler(Vector2 position)
{
    setTexture();
    m_position = position;
    m_speed = 0.2;
    m_laser_speed = 2;
    m_fireRate = 0.5;
    m_health = 7;
    m_type = 1;
    std::cout << "PROWLER entity created!" << "\n";
}

Prowler::~Prowler()
{
    UnloadTexture(m_image);
    std::cout << "PROWLER entity destroyed!" << "\n";
}

void Prowler::update()
{
    if (nearPlayer && !clicked){
        fireLaser();
    }
    drawEnemyLaser();
    updateLaser();
    deleteLaser();
    showStats();
    chasePlayer();
}

void Prowler::behave(Vector2 playerPos)
{
    //calls default enemy behave function
    Enemy::behave(playerPos);

    //unique prowler behave function
    checkArea(playerPos);
    if (nearPlayer){
        m_speed = 1.5;
    } else{
        m_speed = 0.1;
    }
}

void Prowler::setTexture()
{
    m_image=LoadTexture("../Resources/alien_1.png");
}

bool Prowler::checkArea(Vector2 playerPos)
{
    if (pyDistance(getPos(), playerPos) < 250){
        nearPlayer = true;
    } else{
        nearPlayer = false;
    }
    return nearPlayer;
}

float Prowler::pyDistance(Vector2 enemyPos, Vector2 playerPos)
{
    float result = (enemyPos.x - playerPos.x)*(enemyPos.x - playerPos.x) + 
        (enemyPos.y - playerPos.y)*(enemyPos.y - playerPos.y);
    return sqrt(result);
}

void Prowler::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void Prowler::chasePlayer()
{
    if (nearPlayer){
        m_speed = 1.5;
    } else{
        m_speed = 0.1;
    }
}
