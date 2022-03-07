#pragma once
#include "BaseBoid.h"
class PredatorBoid :
    public BaseBoid
{
public:
    PredatorBoid(float alignment, float cohesion, float separation, int id,
        int x = rand() % GWIDTH, int y = rand() % HEIGHT);

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
    sf::Vector2f Alignment();
    sf::Vector2f Cohesion();
    sf::Vector2f Separation();

    sf::Vector2f ChaseBoid();
    float chasingForce = 10;
};

