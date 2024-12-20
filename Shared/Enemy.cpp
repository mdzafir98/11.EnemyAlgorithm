#include "Enemy.h"

Enemy::Enemy()
{
    setTexture();
}

Enemy::Enemy(Vector2 position, float speed = 1.f, int laser_speed = 5, float fireRate = 0.35)
    : m_position{position}, m_speed{speed}, m_laser_speed{laser_speed}, m_fireRate{fireRate}
{
    setTexture();
    std::cout << "ENEMY entity created!" << "\n";
}

Enemy::~Enemy()
{
    UnloadTexture(m_image);
    std::cout << "ENEMY entity destroyed!" << "\n";
}

void Enemy::draw()
{
    DrawTextureV(m_image,m_position,WHITE);
}

void Enemy::update()
{
    if (!clicked){
        fireLaser();
    }
    drawEnemyLaser();
    updateLaser();
    deleteLaser();
    showStats();
}

void Enemy::mouseClicked()
{
    if (clicked==false){
        clicked = true;
    } else{
        clicked = false;
    }
}

void Enemy::setTexture()
{
    m_image=LoadTexture("../Resources/alien_3.png");
}

void Enemy::showStats()
{
    if (clicked==true){
        drawStats();
    }
}

void Enemy::drawStats()
{
    DrawText(TextFormat("SPD: %.2f", m_speed),m_position.x, m_position.y-10, 8, {255,255,255,200});
    DrawText(TextFormat("FR: %.2f", m_fireRate),m_position.x, m_position.y-20, 8, {255,255,255,200});
    DrawText(TextFormat("HP: %i", m_health),m_position.x, m_position.y-30, 8, {255,255,255,200});
}

void Enemy::getDamaged(int damage)
{
    if (m_health > 0){
        m_health -= damage;
    } else{
        m_health = 0;
    }
}

void Enemy::fireLaser()
{
    double currentTime = GetTime();
    if (currentTime - lastFireTime >= m_fireRate){
        lasers.push_back(Laser({m_position.x+m_image.width/2-2, m_position.y},m_laser_speed));
        lastFireTime=GetTime();
    }
}

void Enemy::moveLeft()
{
    m_position.x-=m_speed;
    if (m_position.x<0){
        m_position.x=0;
    }
}

void Enemy::moveRight()
{
    m_position.x+=m_speed;
    if (m_position.x + m_image.width>GetScreenWidth()){
        m_position.x = GetScreenWidth() - m_image.width;
    }
}

void Enemy::moveDown()
{
    m_position.y += m_speed;
}

void Enemy::moveUp()
{
    m_position.y -= m_speed;
    if (m_position.y < 0){
        m_position.y = 0;
    }
}

void Enemy::behave(Vector2 playerPos)
{
    if (alive && clicked == false){
        if (playerPos.x > m_position.x){
            moveRight();
        } else{
            moveLeft();
        }
        if (playerPos.y - m_position.y < 200){
            moveUp();
        } else{
            moveDown();
        }
    }
}

Vector2 Enemy::getPos()
{
    return m_position;
}

void Enemy::setPos(Vector2 position)
{
    m_position = position;
}

Rectangle Enemy::getRect()
{
    return {m_position.x, m_position.y, 
        float(m_image.width), float(m_image.height)};
}

void Enemy::accept(Visitor *visitor)
{
    visitor->visit(this);
}

void Enemy::drawEnemyLaser()
{
    for (auto& laser:lasers){
        laser.draw();
    }
}

void Enemy::updateLaser()
{
    for (auto& laser:lasers){
        laser.update();
    }
}

void Enemy::deleteLaser()
{
    for (auto it = lasers.begin(); it != lasers.end();){
        if (!it->active){
            it = lasers.erase(it);
        } else{
            ++it;
        }
    }
}
