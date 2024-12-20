#pragma once
#include "Visitor.h"
#include "Enemy.h"

class ConcreteVisitor : public Visitor{
public:
    void visit(Enemy* base) override{
        
    }
};