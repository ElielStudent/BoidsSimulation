#pragma once
#include <list>
#include "Boid.h"
#include "UserBoid.h"
#include "PredatorBoid.h"
#include "QuadTree.h"

class Flock {
public:
	Flock(int flID);
	BaseBoid* AddBoid(BoidType bType);
	BaseBoid* AddBoid(int x, int y, BoidType bType);
	void InsertBoids(QuadTree<BaseBoid>* QT);	//Insert the flock's boids into the quadtree referenced
	void UpdateBoids(QuadTree<BaseBoid>* QT);
	void ClearFlock();
	void DrawFlock(sf::RenderWindow& window);
	BaseBoid* getBoid(int id);
	std::list<BaseBoid*>& getBoids() { return this->boids; };

	void setAlignment(float alignmentForce);
	void setCohesion(float cohesionForce);
	void setSeparation(float separationForce);

	float getAlignment() { return alignmentForce; }
	float getCohesion() { return cohesionForce; }
	float getSeparation() { return separationForce; }

	void setDrawRange(bool state);
	void setDrawNear(bool state);
	void setDrawTrail(bool state);
	void setDrawHighlight(bool state);

	int setBoidIndexFrom(int num);
	BaseBoid* getCurrBoid() { return currBoid; };
	int getFLID() { return flID; };
private:
	int flID;
	int fCount = 0;
	BaseBoid* currBoid;
	int currBoidIndex;
	sf::Color color;
	std::list<BaseBoid*> boids;

	float alignmentForce;
	float cohesionForce;
	float separationForce;
};

