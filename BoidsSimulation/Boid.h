#pragma once
#include "BaseBoid.h"
class Boid :
    public BaseBoid
{
public:
    void calcDirection(std::list<BaseBoid*>& boids);
};

