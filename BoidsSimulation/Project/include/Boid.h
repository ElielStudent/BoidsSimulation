#pragma once
#include "BaseBoid.h"
#include <list>

class Boid :
	public BaseBoid
{
public:
	Boid(float alignment, float cohesion, float separation, int id, int flID,
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

	sf::Vector2f Alignment();
	sf::Vector2f Cohesion();
	sf::Vector2f Separation();
	sf::Vector2f Escape();

	float escapeForce;
};

