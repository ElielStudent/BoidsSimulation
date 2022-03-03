#pragma once
#include "BaseBoid.h"
#include <list>

class Boid :
    public BaseBoid
{
public:
	Boid(float alignment, float cohesion, float separation, int id,
		int x = rand() % GWIDTH, int y = rand() % HEIGHT);
    void calcDirection();

	void setAlignment(float alignmentForce) { this->alignmentForce = alignmentForce; }
	void setCohesion(float cohesionForce) { this->cohesionForce = cohesionForce; }
	void setSeparation(float separationForce) { this->separationForce = separationForce; }
	float getAlignment() { return alignmentForce; }
	float getCohesion() { return cohesionForce; }
	float getSeparation() { return separationForce; }
private:

	float alignmentForce;
	float cohesionForce;
	float separationForce;

	Vector2f Alignment();
	Vector2f Cohesion();
	Vector2f Separation();
	Vector2f Escape();


	float escapeForce;
};

