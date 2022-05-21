#pragma once
#include "QuadTree.h"
#include <iostream>
class World{
public:
	World();
	void drawWorld(sf::RenderWindow& window);
	void Zoom(float zAmount);
	void changeSize(sf::Vector2f size);
	void ReGenerateWorld();
	void setView(sf::Vector2f pos);
	void setDefaultView();
private:
	sf::RenderTexture gridTexture;
	sf::Sprite gridSprite;
	sf::View WorldV;
	bool grid[WORLDSIZE][WORLDSIZE] = { {1} };
	bool lastGrid[WORLDSIZE][WORLDSIZE] = { {1} };

	void GenerateTexture();
	void GenerateWorld();
	void fillRandom();
	int getNeighbors(int x, int y);
	void copyWorld();
	//QuadTree<sf::Vector2f> obstacles;
	int numberOfSteps = 7;
};

