#pragma once
#include "Button.h"
#include "BToggle.h"
#include "Label.h"
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

	sf::RectangleShape background;
	Simulation* simulation; //Communicate between the buttons and the simulation
	list<UIElement*> UIElements;
};

