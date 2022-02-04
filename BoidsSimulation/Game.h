#pragma once
#include "SFML/Graphics.hpp"
#include "Flock.h"
#include "constants.h"
#include "Button.h"
#include "World.h"

class Game{
public:
	Game();
	void Start();
	void AddFlock();
private:
	void LoadGame();
	void LoadButtons();
	void LoadViews();
	void HandleEvents();
	void HandleButtons(Vector2i mousePos);
	void Update();
	void Draw();

	void DrawMenu();
	void DrawGame();

	sf::RenderWindow window;
	sf::View WorldV;
	sf::View SimulationV;
	sf::View MenuV;

	list<Flock> flocks;
	int flockCount = 0;				//Amount of flocks
	int currFlock = 0;				//The selected flock (used for adding boids,etc)
	QuadTree QT;					//The quadtree that holds all of the boids and updates every frame
	World world;					//The world that holds the map and the collision obstacles

	Button buttons[10];
	Button bFlock;
	Button bSeparation;
	Button bCohesion;
	Button bAlignment;
	Button bSeparationPlus;
	Button bCohesionPlus;
	Button bAlignmentPlus;
	Button bSeparationMinus;
	Button bCohesionMinus;
	Button bAlignmentMinus;
};

