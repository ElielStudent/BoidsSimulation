#pragma once
#include "SFML/Graphics.hpp"
#include "Flock.h"
#include "constants.h"
#include "Button.h"

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

	sf::RenderWindow window;
	sf::View SimulationV;
	sf::View MenuV;

	list<Flock> flocks;
	int flockCount = 0;
	int currFlock = 0;
	QuadTree QT;

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

