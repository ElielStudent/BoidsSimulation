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
	sf::RenderTexture gridTexture;
	sf::Sprite gridSprite;
	sf::View WorldV;
	void GenerateTexture();
	void GenerateWorld();
	void fillRandom();
	int getNeighbors(int x, int y);
	void copyWorld();
	bool grid[WORLDSIZE][WORLDSIZE] = { {1} };
	bool lastGrid[WORLDSIZE][WORLDSIZE] = { {1} };
	//QuadTree obstacles;

	int numberOfSteps = 7;
};

