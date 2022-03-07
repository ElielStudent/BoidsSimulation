#include "Menu.h"

Menu::Menu() {
	MenuV.setCenter(MWIDTH / 2, MHEIGHT / 2);
	MenuV.setSize(MWIDTH, MHEIGHT);
	MenuV.setViewport(sf::FloatRect(0, 0, MWIDTHPer, 1.f));
	background.setPosition(5, 5);
	background.setSize({ MWIDTH - 10, MHEIGHT - 10 });
	background.setFillColor(sf::Color::Blue);
	background.setOutlineColor(sf::Color::Magenta);
	background.setOutlineThickness(5);
	simulation = nullptr;
	LoadButtons();
}

void Menu::Update(sf::RenderWindow& window) {
	for (UIElement* ui : UIElements) {
		ui->Update(window);
	}
}

void Menu::setSimulation(Simulation* simulation) {
	this->simulation = simulation;
}

void Menu::Draw(sf::RenderWindow& window) {
	window.setView(MenuV);
	window.draw(background);
	for (UIElement* element : UIElements) {
		element->Draw(window);
	}
}

void Menu::LoadButtons() {
	//Simulation zoom in
	auto szin = [this]() {simulation->changeSize({ -30,-30 }); };
	UIElements.push_back(new Button("S +", { 60,GHEIGHT - 100 }, { 100, 50 }, szin));

	//Simulation zoom out
	auto szout = [this]() {simulation->changeSize({ 30,30 }); };
	UIElements.push_back(new Button("S -", { 60,GHEIGHT - 200 }, { 100,50 }, szout));

	//World zoom in
	auto wzin = [this]() {simulation->getWorld()->changeSize({ -30,-30 }); };
	UIElements.push_back(new Button("W +", { 60,GHEIGHT - 300 }, { 100,50 }, wzin));

	//World Zoom out
	auto wzout = [this]() {simulation->getWorld()->changeSize({ 30,30 }); };
	UIElements.push_back(new Button("W -", { 60,GHEIGHT - 400 }, { 100,50 }, wzout));

	//Toggle QuadTree
	auto quadToggle = [this]() {simulation->toggleDrawQuad(); };
	UIElements.push_back(new BToggle("QT", { 60,GHEIGHT - 500 }, { 100,50 }, quadToggle));
}

void Menu::LoadMenu(MenuType menuType, sf::RenderWindow& window) {
	currMenu = menuType;
	switch (menuType) {
	case(MenuType::eWorldMenu):
		LoadWorldMenu(window);
		break;
	case(MenuType::eFlockMenu):
		LoadFlockMenu(window);
		break;
	case(MenuType::eBoidMenu):
		LoadBoidMenu(window);
		break;
	default:
		LoadWorldMenu(window);
	}
}

void Menu::LoadWorldMenu(sf::RenderWindow& window) {
	// World Gen: blank with walls on the outside, cave generated map, premade map with obstacles and neural network
	// In neural network (with different tabs), you can select a pre trained network or let one learn for
	// some generations. You can take out flock mode (or put it in world menu before you select this mode) and instead 
	// add a screen pre start that selects what the boid is rewarded for. Before starting you can choose 
	// - Surviving with predator boids (amount of predators is pre defined but can be changed)
	// - Most amount of normal boids eaten (Can spawn new normal boids every x amount of time that can be changed or you can add more boids),
	// 

	//Restart button (deletes boids and generates a new map)
	//Choos

}

void Menu::LoadFlockMenu(sf::RenderWindow& window) {
	//Adds outline to all boids of flock based on which one is selected
	//Add boid
	//Choose to add predator flock
	//Delete flocks
}

void Menu::LoadBoidMenu(sf::RenderWindow& window) {
	//Choose between boids in flock
	//Add user boid
	//Select isHidden
	//Delete boid
	//Buttons for range,nearby,trail
	//add user boid to flock
}

