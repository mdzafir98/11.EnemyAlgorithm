#pragma once

//forward declaration
class Enemy;
class Prowler;

class Visitor{
public:
    virtual ~Visitor() = default;
    virtual void visit(Enemy* enemy) = 0;
    virtual void visit(Prowler* prowler) = 0;
};