#pragma once
#include "Button.h"
#include "BToggle.h"
#include "Label.h"
#include "Simulation.h"

enum class MenuType{eWorldMenu,eBoidMenu,eFlockMenu};

class Menu 
{
public:
	Menu();
	void Update(RenderWindow& window);
	void setSimulation(Simulation* simulation);
	void Draw(RenderWindow& window);
	void LoadButtons();
	void LoadMenu(MenuType menuType,RenderWindow& window);
private:
	void LoadWorldMenu(RenderWindow& window);
	void LoadFlockMenu(RenderWindow& window);
	void LoadBoidMenu(RenderWindow& window);

	MenuType currMenu = MenuType::eWorldMenu;
	View MenuV;

	sf::RectangleShape background;
	Simulation* simulation; //Communicate between the buttons and the simulation
	list<UIElement*> UIElements;
};

