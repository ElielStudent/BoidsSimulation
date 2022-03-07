#pragma once
#include <list>
#include "Boid.h"
#include "UserBoid.h"
#include "QuadTree.h"

class Flock {
public:
	Flock(int id);
	void AddBoid();
	void AddBoid(int x, int y);
	void InsertBoids(QuadTree<BaseBoid>* QT);	//Insert the boids into the quadtree
	void UpdateBoids(QuadTree<BaseBoid>* QT);
	void ClearFlock();
	void DrawFlock(sf::RenderWindow& window);

	void setAlignment(float alignmentForce);
	void setCohesion(float cohesionForce);
	void setSeparation(float separationForce);
	float getAlignment() { return alignmentForce; }
	float getCohesion() { return cohesionForce; }
	float getSeparation() { return separationForce; }
private:
	int flID;
	int fCount = 0;
	sf::Color color;

	std::list<BaseBoid*> boids;
	float alignmentForce;
	float cohesionForce;
	float separationForce;
};

