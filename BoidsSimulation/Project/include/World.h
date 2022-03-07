#pragma once
#include "QuadTree.h"
#include <iostream>
class World{
public:
	World();
	void drawWorld(sf::RenderWindow& window);
	void Zoom(float zAmount);
	void changeSize(sf::Vector2f size);
private:
	sf::View WorldV;
	void GenerateWorld();
	void fillRandom();
	int getNeighbors(int x, int y);
	void copyWorld();
	bool lastGrid[WORLDSIZE][WORLDSIZE] = { {1} };
	bool grid[WORLDSIZE][WORLDSIZE] = { {1} };
	//QuadTree obstacles;
};

