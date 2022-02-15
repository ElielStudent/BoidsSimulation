#pragma once
#include "Boid.h"
#include "constants.h"

using namespace sf;

class QuadTree {
public:
	QuadTree();
	QuadTree(int level, FloatRect boundary);
	void SubDivide();
	bool Insert(Boid *boid);
	void Draw(RenderWindow& window);
	void Query(FloatRect boundary, list<Boid*>* boidList);
	void Clear();
private:
	/*QuadTree* tLeft;
	QuadTree* tRight;
	QuadTree* bLeft;
	QuadTree* bRight;*/
	QuadTree* subNodes[4];

	list<Boid*> boids;				//Boids stored in level
	FloatRect boundary;				//Boundary of the current quadtree level
	int capacity;					//Max number of boids before dividing 
	int level;						//Depth of level
	bool isDivided;					//If the quadtree has divided yet or not
};



