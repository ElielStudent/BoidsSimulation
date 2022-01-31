#pragma once
#include "Boid.h"
#include "constants.h"

typedef struct Rectangle {
	int x, y;				//Top left of the rectangle
	int width, height;
}Rectangle;

class QuadTree {
public:
	QuadTree();
	QuadTree(Rectangle boundary);
	void SubDivide();
	void Insert(Boid boid);
	void Draw(RenderWindow& window);
private:
	QuadTree* tLeft;
	QuadTree* bLeft;
	QuadTree* tRight;
	QuadTree* bRight;

	list<Boid> boids;				//Boids stored in level
	Rectangle boundary;
	int capacity;					//Max number of boids before dividing (20)
	bool isDivided;
};

bool inBounds(Rectangle boundary, Vector2f point);	//Checks whether a point is in the rectangle bound

