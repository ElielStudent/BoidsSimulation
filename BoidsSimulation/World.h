#pragma once
#include "QuadTree.h"
#include <iostream>
class World{
public:
	World();
	void drawWorld(RenderWindow& window);
	void Zoom(float zAmount);
	void changeSize(Vector2f size);
private:
	View WorldV;
	void GenerateWorld();
	void fillRandom();
	int getNeighbors(int x, int y);
	void copyWorld();
	bool lastGrid[WORLDSIZE][WORLDSIZE] = { {1} };
	bool grid[WORLDSIZE][WORLDSIZE] = { {1} };
	QuadTree obstacles;
};

