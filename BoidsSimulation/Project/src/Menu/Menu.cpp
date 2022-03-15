#include "Menu.h"

Menu::Menu(sf::RenderWindow& window) :window(window) {
	MenuV.setCenter(MWIDTH / 2, MHEIGHT / 2);
	MenuV.setSize(MWIDTH, MHEIGHT);
	MenuV.setViewport(sf::FloatRect(0, 0, MWIDTHPer, 1.f));

	background.setPosition(5, 5);
	background.setSize({ MWIDTH - 10, MHEIGHT - 10 });
	background.setFillColor(sf::Color::Blue);
	background.setOutlineColor(sf::Color::Magenta);
	background.setOutlineThickness(5);
	simulation = nullptr;

	auto worldMenu = [this]() {LoadMenu(eWorldMenu); };
	UITabs.push_back(new BToggle(" GAME", { 5,GHEIGHT - 105 }, { 123,100 }, worldMenu, sf::Color::Cyan));
	UITabs.front()->SetState(true);	//Default menu type

	auto flockMenu = [this]() {LoadMenu(eFlockMenu); };
	UITabs.push_back(new BToggle(" FLOCK", { 126,GHEIGHT - 105 }, { 123,100 }, flockMenu, sf::Color::Green));

	auto boidMenu = [this]() {LoadMenu(eBoidMenu); };
	UITabs.push_back(new BToggle(" BOID", { 247,GHEIGHT - 105 }, { 123,100 }, boidMenu, sf::Color::Red));

	LoadMenu(eWorldMenu);			//Default menu type
}

void Menu::Update() {
	window.setView(MenuV);
	for (UIElement* ui : UIElements) {
		ui->Update(window);
	}
	for (UIElement* tabs : UITabs) {
		tabs->Update(window);
	}
}

void Menu::setSimulation(Simulation* simulation) {
	this->simulation = simulation;
}

void Menu::Draw() {
	window.setView(MenuV);
	window.draw(background);
	for (UIElement* element : UIElements) {
		element->Draw(window);
	}
	for (BToggle* tabs : UITabs) {
		tabs->Draw(window);
	}
}

void Menu::RestartMenu(MenuType menuType) {
	UIElements.clear();
	int index = 0;
	for (auto it = UITabs.begin(); it != UITabs.end(); it++) {	//Turns off any toggles if you press another
		(*it)->SetState(index++ == menuType);
	}
}

void Menu::LoadMenu(MenuType menuType) {
	RestartMenu(menuType);
	currMenu = menuType;
	switch (menuType) {
	case(eWorldMenu):
		LoadWorldMenu();
		break;
	case(eFlockMenu):
		LoadFlockMenu();
		break;
	case(eBoidMenu):
		LoadBoidMenu();
		break;
	default:
		LoadWorldMenu();
	}
}

void Menu::LoadWorldMenu() {
	//Simulation zoom in
	auto szin = [this]() {simulation->changeSize({ -30,-30 }); };
	UIElements.push_back(new Button("S +", { 60, 100 }, { 100, 50 }, szin));

	//Simulation zoom out
	auto szout = [this]() {simulation->changeSize({ 30,30 }); };
	UIElements.push_back(new Button("S -", { 60, 200 }, { 100,50 }, szout));

	//World zoom in
	auto wzin = [this]() {simulation->getWorld()->changeSize({ -30,-30 }); };
	UIElements.push_back(new Button("W +", { 60, 300 }, { 100,50 }, wzin));

	//World Zoom out
	auto wzout = [this]() {simulation->getWorld()->changeSize({ 30,30 }); };
	UIElements.push_back(new Button("W -", { 60, 400 }, { 100,50 }, wzout));

	//Toggle QuadTree
	auto quadToggle = [this]() {simulation->toggleDrawQuad(); };
	UIElements.push_back(new BToggle("QT", { 60, 500 }, { 100,50 }, quadToggle));

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

void Menu::LoadFlockMenu() {
	Label* flockIndex = new Label("0", { 138, 70 }, { 50,50 });
	auto updateFlockIndex = [this, flockIndex]() {flockIndex->SetText(std::to_string(simulation->getCurrFlockIndex()+1)); };
	flockIndex->SetFunction(updateFlockIndex);
	UIElements.push_back(flockIndex);

	auto subF = [this]() {simulation->setFlockIndexFrom(-1); };
	UIElements.push_back(new Button("FL-", { 60, 50 }, { 70,90 }, subF));

	auto addF = [this]() {simulation->setFlockIndexFrom(1); };
	UIElements.push_back(new Button("FL+", { 200, 50 }, { 70,90 }, addF));

	auto addFlock = [this]() {simulation->AddFlock(); };
	UIElements.push_back(new Button("New Flock", { 60, 200 }, { 200,80 }, addFlock));

	auto addNB = [this]() {simulation->getCurrFlock()->AddBoid(BoidType::eNormalBoid); };
	UIElements.push_back(new Button("Boid +", { 60, 400 }, { 150,70 }, addNB));

	auto addPB = [this]() {simulation->getCurrFlock()->AddBoid(BoidType::ePredatorBoid); };
	UIElements.push_back(new Button("PBoid +", { 60, 500 }, { 150,70 }, addPB));

	auto addUB = [this]() {simulation->getCurrFlock()->AddBoid(BoidType::eUserBoid); };
	UIElements.push_back(new Button("UBoid +", { 60, 600 }, { 150,70 }, addUB));

	//No 2 another color
	/*auto setColor2 = [this]() {simulation->getFlock(1)->GetBoid(2)->setColor(sf::Color::Red); };
	UIElements.push_back(new Button("2 2 R", { 60, 700 }, { 100,50 }, setColor2));*/


	//Flock Selection
	//Adds outline to all boids of flock based on which one is selected
	//Add boid
	//Choose to add predator flock
	//Delete flocks
	//Change flock separation,cohesion,alignment
}

void Menu::LoadBoidMenu() {
	//Choose between boids in flock
	//Add user boid
	//Select isHidden
	//Delete boid
	//Buttons for range,nearby,trail
	//add user boid to flock
}

