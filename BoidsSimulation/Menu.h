#pragma once
#include "Button.h"
#include "Simulation.h"
class Menu 
{
public:
	Menu();
	void setSimulation(Simulation* simulation);
	void Draw(RenderWindow& window);
	void LoadButtons();
	void HandleButtons(Vector2i mousePos);
private:
	View MenuV;

	Simulation* simulation; //Communicate between the buttons and the simulation
	Button buttons[5];
	Button sZoomIn;
	Button sZoomOut;
	Button wZoomIn;
	Button wZoomOut;
	Button qtToggle;
};

