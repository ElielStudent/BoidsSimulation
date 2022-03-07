#pragma once
#include "BaseBoid.h"
#include "constants.h"
#include "Functions.h"

template <typename T>
class QuadTree {
public:
	QuadTree();
	QuadTree(int level, sf::FloatRect boundary);
	void SubDivide();
	bool Insert(T* boid);
	void Draw(sf::RenderWindow& window);
	void Query(sf::FloatRect boundary, std::list<T*>* boidList, BoidType boidType = BoidType::eBaseBoid);
	void Query(sf::Vector2f position,float visualRadius, std::list<T*>* boidList,BoidType boidType = BoidType::eBaseBoid);
	void Clear();
private:
	QuadTree* subNodes[4];

	std::list<T*> boids;					//Boids stored in level
	sf::FloatRect boundary;				//Boundary of the current quadtree level
	int capacity;					//Max number of boids before dividing 
	int level;						//Depth of level
	bool isDivided;					//If the quadtree has divided yet or not
};