#pragma once
#include "Button.h"
#include "Simulation.h"
class Menu 
{
public:
	Menu();
	void Update(RenderWindow& window);
	void setSimulation(Simulation* simulation);
	void Draw(RenderWindow& window);
	void LoadButtons();
private:
	View MenuV;

	Simulation* simulation; //Communicate between the buttons and the simulation
	list<UIElement*> UIElements;
	
};

