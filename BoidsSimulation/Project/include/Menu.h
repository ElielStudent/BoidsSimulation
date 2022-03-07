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
	void Update(sf::RenderWindow& window);
	void setSimulation(Simulation* simulation);
	void Draw(sf::RenderWindow& window);
	void LoadButtons();
	void LoadMenu(MenuType menuType,sf::RenderWindow& window);
private:
	void LoadWorldMenu(sf::RenderWindow& window);
	void LoadFlockMenu(sf::RenderWindow& window);
	void LoadBoidMenu(sf::RenderWindow& window);

	MenuType currMenu = MenuType::eWorldMenu;
	sf::View MenuV;

	sf::RectangleShape background;
	Simulation* simulation; //Communicate between the buttons and the simulation
	std::list<UIElement*> UIElements;
};

