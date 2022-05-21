#pragma once
#include "Button.h"
#include "BToggle.h"
#include "Label.h"
#include "Slider.h"
#include "Simulation.h"

enum MenuType{eWorldMenu, eFlockMenu,eBoidMenu};

class Menu 
{
public:
	Menu(sf::RenderWindow& window);
	void Update();
	void setSimulation(Simulation* simulation);
	void Draw();
	void LoadMenu(MenuType menuType);
private:
	void RestartMenu(MenuType menuType);
	void LoadWorldMenu();
	void LoadFlockMenu();
	void LoadBoidMenu();

	MenuType currMenu = eWorldMenu;
	sf::RenderWindow& window;
	sf::View MenuV;
	sf::RectangleShape background;
	Simulation* simulation; //Communicate between the buttons and the simulation
	std::list<BToggle*> UITabs;
	std::list<UIElement*> UIElements;
};

