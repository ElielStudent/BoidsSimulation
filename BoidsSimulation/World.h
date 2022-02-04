#pragma once
#include "QuadTree.h"
class World{
public:
	World();
	void drawWorld(RenderWindow& window);
private:
	void GenerateWorld();
	void fillRandom();
	int getNeighbors(int x, int y);
	void copyWorld();
	void getWorld();
	bool lastGrid[WORLDSIZE][WORLDSIZE] = { {0} };
	bool grid[WORLDSIZE][WORLDSIZE] = { {0} };
	QuadTree obstacles;
};

