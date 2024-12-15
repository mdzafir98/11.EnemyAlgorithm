#pragma once
#include "Enemy.h"

class Prowler : public Enemy{
public:
    Prowler(Vector2 position);
    void setTexture();
};
