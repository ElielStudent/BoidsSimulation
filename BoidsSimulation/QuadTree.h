#pragma once
#include "Boid.h"
#include "constants.h"

using namespace sf;

class QuadTree {
public:
	QuadTree();
	QuadTree(IntRect boundary);
	void SubDivide();
	void Insert(Boid boid);
	void Draw(RenderWindow& window);
private:
	QuadTree* tLeft;
	QuadTree* bLeft;
	QuadTree* tRight;
	QuadTree* bRight;

	list<Boid> boids;				//Boids stored in level
	IntRect boundary;
	int capacity;					//Max number of boids before dividing (20)
	bool isDivided;
};

bool inBounds(IntRect boundary, Vector2f point);	//Checks whether a point is in the rectangle bound

