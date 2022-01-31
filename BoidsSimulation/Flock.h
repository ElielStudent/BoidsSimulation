#pragma once
#include <list>
#include "Boid.h"
#include "QuadTree.h"
class Flock {
public:
	Flock(int id);
	void AddBoid();
	void AddBoid(int x, int y);
	void UpdateBoids(QuadTree QT);
	void ClearFlock();
	void DrawFlock(sf::RenderWindow& window);

	void setAlignment(float alignmentForce);
	void setCohesion(float cohesionForce);
	void setSeparation(float separationForce);
	float getAlignment() { return alignmentForce; }
	float getCohesion() { return cohesionForce; }
	float getSeparation() { return separationForce; }
private:
	int id;
	int fCount = 0;
	sf::Color color;

	list<Boid*> boids;
	float alignmentForce;
	float cohesionForce;
	float separationForce;
};

