#include "Mothership.h"

Mothership::Mothership(Vector2 position)
{
    setTexture();
    m_position = position;
    m_fireRate = 0;
    m_speed = 0.5;
    m_health = 10;
    m_type = 2;
    std::cout << "MOTHERSHIP entity created!" << "\n";
}

Mothership::~Mothership()
{
    UnloadTexture(m_image);
    std::cout << "MOTHERSHIP entity destroyed!" << "\n";
}

void Mothership::update()
{
    if (!clicked){

    }
    showStats();
}

void Mothership::setTexture()
{
    m_image = LoadTexture("../Resources/mystery.png");
}

void Mothership::behave(Vector2 playerPos)
{
    if (wallFlag==false){
        moveRight();
        if (m_position.x + m_image.width >= GetScreenWidth()){
            wallFlag = true;
        }
    } else if (wallFlag==true){
        moveLeft();
        if (m_position.x <= 0){
            wallFlag = false;
        }
    }

    if (playerPos.y - m_position.y < 400){
        moveUp();
    } else{
        moveDown();
    }

    if (checkArea(playerPos) && spawnCount > 0){
        spawnEnemy();
    }
}

float Mothership::pyDistance(Vector2 enemyPos, Vector2 playerPos)
{
    float result = (enemyPos.x - playerPos.x)*(enemyPos.x - playerPos.x) + 
        (enemyPos.y - playerPos.y)*(enemyPos.y - playerPos.y);
    return sqrt(result);
}

void Mothership::spawnEnemy()
{
    double currentTIme = GetTime();
    if (currentTIme - lastSpawnTime >= lastSpawnTime){
        std::cout << "MOTHERSHIP entity is far. Spawning ENEMY!" << "\n";
        enemies.push_back(new Enemy());
        spawnCount--;
        std::cout << "MOTHERSHIP spawn: " << enemies.size() << "\n";
        lastSpawnTime = GetTime();
    }
}

bool Mothership::checkArea(Vector2 playerPos)
{
    if (pyDistance(getPos(), playerPos)<200){
        nearPlayer = true;
    } else{
        nearPlayer = false;
    }
    return nearPlayer;
}
