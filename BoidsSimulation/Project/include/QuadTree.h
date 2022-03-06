#pragma once
#include "BaseBoid.h"
#include "constants.h"
#include "Functions.h"

using namespace sf;

template <typename T>
class QuadTree {
public:
	QuadTree();
	QuadTree(int level, FloatRect boundary);
	void SubDivide();
	bool Insert(T* boid);
	void Draw(RenderWindow& window);
	void Query(FloatRect boundary, list<T*>* boidList, BoidType boidType = BoidType::eBaseBoid);
	void Query(Vector2f position,float visualRange, list<T*>* boidList,BoidType boidType = BoidType::eBaseBoid);
	void Clear();
private:
	QuadTree* subNodes[4];

	list<T*> boids;					//Boids stored in level
	FloatRect boundary;				//Boundary of the current quadtree level
	int capacity;					//Max number of boids before dividing 
	int level;						//Depth of level
	bool isDivided;					//If the quadtree has divided yet or not
};