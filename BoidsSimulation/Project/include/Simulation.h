#pragma once
#include <list>
#include "QuadTree.h"
#include "World.h"
#include "Flock.h"
#include <iostream>

class Simulation
{
public:
	Simulation();
	Flock* getFlock(int index);
	void UpdateQuadTree();
	void AddFlock();
	void addBoid();
	void Draw(RenderWindow& window);
	void Update();
	void Zoom(float zAmount);
	void changeSize(Vector2f size);
	World* getWorld();
	void toggleDrawQuad();
private:
	bool drawQuad = 0;
	View SimulationV;
	list<Flock> flocks;
	int flockCount = 0;				//Amount of flocks
	//int currFlock = 0;			//The selected flock (used for adding boids,etc)
	Flock* currFlock;
	QuadTree<BaseBoid>* QT;					//The quadtree that holds all of the boids and updates every frame
	World* world;					//The world that holds the map and the collision obstacles
};

