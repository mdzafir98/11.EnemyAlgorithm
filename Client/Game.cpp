#include "Game.h"

Game::Game()
{
    initGame();
    initEnemies();
}

Game::~Game()
{
    delete alien;
}

void Game::draw()
{
    spaceship.draw();
    for (auto& enemy:enemies){
        enemy->draw();
    }
    // alien->draw();
    // prowler->draw();
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
    // if (CheckCollisionPointRec(mousePos,alien->getRect()) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
    //     std::cout << "PAUSED ENEMY ENTITY!" << "\n";
    //     alien->mouseClicked();
    // }
    // if (alien->clicked == true && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    //     alien->setPos({mousePos.x - alien->m_image.width/2,mousePos.y - alien->m_image.height/2});
    // }
}

void Game::handleFireLaser()
{
    if (IsKeyDown(KEY_SPACE)){
            spaceship.fireLaser();
            // std::cout << "firerate: " << spaceship.fireRate << "\n";
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
        // std::cout << "firerate timer: " << fireRateTimer.getTimer(&fireRateTimer) << "\n";
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
    DrawText(TextFormat("Firerate: %.2f", spaceship.fireRate),10,20,20,{255,255,255,20});
    DrawText(TextFormat("Token:  %i", fireRateToken),10,45,20,{255,255,255,20}); 
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
    // alien->update();
    // if (alien->alive && alien->clicked == false){
    //     if (spaceship.getPosition().x > alien->getPos().x){
    //         alien->moveRight();
    //     } else{
    //         alien->moveLeft();
    //     }
    //     if (spaceship.getPosition().y-alien->getPos().y<200){
    //         alien->moveUp();
    //     } else{
    //         alien->moveDown();
    //     }
    // }
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
