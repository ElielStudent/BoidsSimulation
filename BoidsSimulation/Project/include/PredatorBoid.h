#pragma once
#include "BaseBoid.h"
class PredatorBoid :
    public BaseBoid
{
public:
    PredatorBoid( int id,int x = rand() % GWIDTH, int y = rand() % HEIGHT);

    void setAlignment(float alignmentForce) { this->alignmentForce = alignmentForce; }
    void setCohesion(float cohesionForce) { this->cohesionForce = cohesionForce; }
    void setSeparation(float separationForce) { this->separationForce = separationForce; }

    float getAlignment() { return alignmentForce; }
    float getCohesion() { return cohesionForce; }
    float getSeparation() { return separationForce; }
private:
    void calcDirection();

    float alignmentForce;
    float cohesionForce;
    float separationForce;
    Vector2f Alignment();
    Vector2f Cohesion();
    Vector2f Separation();

    Vector2f ChaseBoid();
    float chasingForce = 10;
};

