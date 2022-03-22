#pragma once
#include <list>
#include "QuadTree.h"
#include "World.h"
#include "Flock.h"
#include <iostream>

class Simulation
{
public:
	Simulation(sf::RenderWindow&window);
	Flock* getFlock(int id);
	void UpdateQuadTree();
	void AddFlock();
	void AddBoid();
	void Draw();
	void Update();
	void Zoom(float zAmount);
	void changeSize(sf::Vector2f size);
	World* getWorld();
	void toggleDrawQuad();
	int setFlockIndexFrom(int num);
	Flock* getCurrFlock() { return currFlock; };
private:						  
	bool drawQuad = 0;
	sf::View SimulationV;
	sf::RenderWindow& window;
	std::list<Flock*> flocks;	
	Flock* currFlock;				//Current flock that is selected
	int currFlockIndex;
	QuadTree<BaseBoid>* QT;			//The quadtree that holds all of the boids and updates every frame
	World* world;					//The world that holds the map and the collision obstacles
};

