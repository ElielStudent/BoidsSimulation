#pragma once
#include "SFML/Graphics.hpp"
#include "Flock.h"
#include "constants.h"
#include "Button.h"
#include "World.h"
#include "Simulation.h"
#include "Menu.h"

class Game{
public:
	Game();
	void Start();
private:
	void HandleEvents();
	void Update();
	void Draw();
	Simulation simulation;
	Menu menu;
	sf::RenderWindow window;
};

