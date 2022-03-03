#pragma once
#include "BaseBoid.h"
class PredatorBoid :
    public BaseBoid
{
public:
    PredatorBoid( int id,int x = rand() % GWIDTH, int y = rand() % HEIGHT);

private:
    void calcDirection();
    Vector2f ChaseBoid();
    float chasingForce = 10;
};

