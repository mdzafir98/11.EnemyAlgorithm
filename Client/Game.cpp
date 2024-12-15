#include "Game.h"

Game::Game()
{
    initGame();
    initEnemies();
}

Game::~Game()
{
    for (auto& enemy:enemies){
        delete enemy;
    }
}

void Game::draw()
{
    spaceship.draw();
    for (auto& enemy:enemies){
        enemy->draw();
    }
    for (auto& laser:spaceship.lasers){
        laser.draw();
    }
    drawText();
}

void Game::update()
{
    if (alive){
        for (auto& laser:spaceship.lasers){
            laser.update();
        }
    }
    handleEnemies();
    checkCollisions();
    deleteInactiveLaser();
}

void Game::initGame()
{
    alive=true;
}

void Game::handleInput()
{
    if (alive){
        if (IsKeyDown(KEY_W)){
            spaceship.moveUp();
        } else if (IsKeyDown(KEY_D)){
            spaceship.moveRight();
        } else if (IsKeyDown(KEY_A)){
            spaceship.moveLeft();
        } else if (IsKeyDown(KEY_S)){
            spaceship.moveDown();
        }
        handleFireLaser();
    }

    mousePos = {GetMousePosition()};
    for (auto& enemy:enemies){
        if (CheckCollisionPointRec(mousePos,enemy->getRect()) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
            std::cout << "PAUSED ENEMY ENTITY!" << "\n";
            enemy->mouseClicked();
        }
        if (enemy->clicked == true && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(mousePos, enemy->getRect())){
            enemy->setPos({mousePos.x - enemy->m_image.width/2,mousePos.y - enemy->m_image.height/2});
        }
    }

    changeType();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_H)){
        Enemy* spawn = new Enemy({mousePos},1.f,5,0.5);
        enemies.push_back(spawn);
    }
}

void Game::handleFireLaser()
{
    if (IsKeyDown(KEY_SPACE)){
            spaceship.fireLaser();
        }
    if (GetTime() - lastTime >= 0.5 && IsKeyDown(KEY_F)){
        if (fireRateToken>0){
            --fireRateToken;
            fireRateTimer.startTimer(&fireRateTimer,firerateLife);
            if (!fireRateTimer.TimerDone(&fireRateTimer)){
                spaceship.fireRate=0.2;
                lastTime=GetTime();
            }
        } 
    }
    fireRateTimer.updateTimer(&fireRateTimer);
    if (fireRateTimer.getTimer(&fireRateTimer)<0.f){
        spaceship.fireRate=0.35;
    }
}

void Game::drawText()
{
    drawInterface();
}

void Game::drawInterface()
{
    DrawText(TextFormat("Enemy: %i", enemies.size()),10,445,20,{255,255,255,50});
    DrawText(TextFormat("Firerate: %.2f", spaceship.fireRate),10,465,20,{255,255,255,50});
    DrawText(TextFormat("Token:  %i", fireRateToken),10,485,20,{255,255,255,50});

    DrawText(TextFormat("Enemy type: %i", enemyType),350,485,20,{255,255,255,50}); 
}

void Game::initEnemies()
{
    alien = new Enemy({100,100},1,5,0.5);
    prowler = new Prowler({200,200});
    enemies.push_back(alien);
    enemies.push_back(prowler);
}

void Game::handleEnemies()
{
    for (auto& enemy:enemies){
        enemy->update();
        if (enemy->alive && enemy->clicked == false){
            if (spaceship.getPosition().x > enemy->getPos().x){
                enemy->moveRight();
            } else{
                enemy->moveLeft();
            }
        
            if (spaceship.getPosition().y - enemy->getPos().y < 200){
                enemy->moveUp();
            } else{
                enemy->moveDown();
            }
        }
    }
    prowler->checkArea(spaceship.getPosition());
}

void Game::checkCollisions()
{
    for (auto& laser:spaceship.lasers){
        if (CheckCollisionRecs(alien->getRect(),laser.getRect())){
            alien->getDamaged(1);
            laser.active=false;
        }
    }
}

void Game::deleteInactiveLaser()
{
    for (auto it=spaceship.lasers.begin(); it!=spaceship.lasers.end();){
        if(!it->active){
            it=spaceship.lasers.erase(it);
        } else{
            ++it;
        }
    }
}

void Game::changeType()
{
    if (IsKeyDown(KEY_ONE)){
        enemyType = 1;
    } else if (IsKeyDown(KEY_TWO)){
        enemyType = 2;
    } else if (IsKeyDown(KEY_ZERO)){
        enemyType = 0;
    }
}
