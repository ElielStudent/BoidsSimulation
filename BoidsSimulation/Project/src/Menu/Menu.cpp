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
	UITabs.push_back(new BToggle(" GAME", { 5,GHEIGHT - 105 }, { 123,100 }, worldMenu));
	UITabs.front()->SetState(true);	//Default menu type

	auto flockMenu = [this]() {LoadMenu(eFlockMenu); };
	UITabs.push_back(new BToggle(" FLOCK", { 126,GHEIGHT - 105 }, { 123,100 }, flockMenu));

	auto boidMenu = [this]() {LoadMenu(eBoidMenu); };
	UITabs.push_back(new BToggle(" BOID", { 247,GHEIGHT - 105 }, { 123,100 }, boidMenu));

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
	for (UIElement* ui : UIElements)
		delete ui;
	UIElements.clear();
	UIElements.erase(UIElements.begin(), UIElements.end());
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
	////Simulation zoom in
	//auto szin = [this]() {simulation->changeSize({ -30,-30 }); };
	//UIElements.push_back(new Button("S +", { 60, 100 }, { 100, 50 }, szin));

	////Simulation zoom out
	//auto szout = [this]() {simulation->changeSize({ 30,30 }); };
	//UIElements.push_back(new Button("S -", { 60, 200 }, { 100,50 }, szout));

	////World zoom in
	//auto wzin = [this]() {simulation->getWorld()->changeSize({ -30,-30 }); };
	//UIElements.push_back(new Button("W +", { 60, 300 }, { 100,50 }, wzin));

	////World Zoom out
	//auto wzout = [this]() {simulation->getWorld()->changeSize({ 30,30 }); };
	//UIElements.push_back(new Button("W -", { 60, 400 }, { 100,50 }, wzout));

	//Toggle QuadTree
	auto quadToggleOn = [this]() {simulation->setDrawQuad(true); };
	auto quadToggleOff = [this]() {simulation->setDrawQuad(false); };
	UIElements.push_back(new BToggle("QT", { 75, 100 }, { 200,150 }, quadToggleOn, quadToggleOff));

	//Regenerate the world
	auto regenW = [this]() {simulation->getWorld()->ReGenerateWorld(); };
	UIElements.push_back(new Button("REGEN W", { 75, 300 }, { 200,150 }, regenW));

	//Reset Simulation
	auto resetF = [this]() {simulation->resetSim(); };
	UIElements.push_back(new Button("RESTART", { 75, 500 }, { 200,150 }, resetF));


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
	//Flock Indexing
	Label* flockIndex = new Label("1", { 153, 70 }, { 50,50 });
	auto updateFlockIndex = [this, flockIndex]() {flockIndex->SetText(std::to_string(simulation->getCurrFlock()->getFLID() + 1)); };
	flockIndex->SetFunction(updateFlockIndex);
	UIElements.push_back(flockIndex);

	auto subF = [this]() {simulation->setFlockIndexFrom(-1); };
	UIElements.push_back(new Button("FL-", { 75, 50 }, { 70,90 }, subF));

	auto addF = [this]() {simulation->setFlockIndexFrom(1); };
	UIElements.push_back(new Button("FL+", { 215, 50 }, { 70,90 }, addF));

	//Flock add
	auto addFlock = [this]() {simulation->AddFlock(); };
	UIElements.push_back(new Button("Add Flock", { 86, 150 }, { 190,80 }, addFlock));

	//Adding boid functions
	auto addNB = [this]() {simulation->AddBoid(BoidType::eNormalBoid); };
	UIElements.push_back(new Button("Boid +", { 60, 500 }, { 150,70 }, addNB));

	auto addPB = [this]() {simulation->AddBoid(BoidType::ePredatorBoid); };
	UIElements.push_back(new Button("PBoid +", { 60, 600 }, { 150,70 }, addPB));

	auto addUB = [this]() {simulation->AddBoid(BoidType::eUserBoid); };
	UIElements.push_back(new Button("UBoid +", { 60, 700 }, { 150,70 }, addUB));

	//Toggle functions
	auto togHigOn = [this]() {simulation->getCurrFlock()->setDrawHighlight(true); };
	auto togHigOff = [this]() {simulation->getCurrFlock()->setDrawHighlight(false); };
	UIElements.push_back(new BToggle(" Highlight", { 20, 300 }, { 150,80 }, togHigOn, togHigOff));

	auto togNeiOn = [this]() {simulation->getCurrFlock()->setDrawNear(true); };
	auto togNeiOff = [this]() {simulation->getCurrFlock()->setDrawNear(false); };
	UIElements.push_back(new BToggle("Nearby", { 200, 300 }, { 150,80 }, togNeiOn, togNeiOff));

	auto togRanOn = [this]() {simulation->getCurrFlock()->setDrawRange(true); };
	auto togRanOff = [this]() {simulation->getCurrFlock()->setDrawRange(false); };
	UIElements.push_back(new BToggle("Range", { 20, 400 }, { 150,80 }, togRanOn, togRanOff));

	auto togTraOn = [this]() {simulation->getCurrFlock()->setDrawTrail(true); };
	auto togTraOff = [this]() {simulation->getCurrFlock()->setDrawTrail(false); };
	UIElements.push_back(new BToggle("Trail", { 200, 400 }, { 150,80 }, togTraOn, togTraOff));


	//Flock Selection
	//Adds outline to all boids of flock based on which one is selected
	//Add boid
	//Delete boid
	//Choose to add predator flock
	//Delete flocks
	//Change flock separation,cohesion,alignment
}

void Menu::LoadBoidMenu() {
	//Flock Indexing
	Label* flockText = new Label("Flock:", { 55, 50 }, { 120,50 });
	UIElements.push_back(flockText);

	Label* flockIndex = new Label("1", { 185, 50 }, { 60,50 });
	auto updateFlockIndex = [this, flockIndex]() {flockIndex->SetText(std::to_string(simulation->getCurrFlock()->getFLID() + 1)); };
	flockIndex->SetFunction(updateFlockIndex);
	UIElements.push_back(flockIndex);

	auto addF = [this]() {simulation->setFlockIndexFrom(1); };
	UIElements.push_back(new Button("+", { 255, 50 }, { 50,50 }, addF));

	//Boid Indexing
	Label* boidIndex = new Label("1", { 153, 160 }, { 50,50 });
	auto updateBoidIndex = [this, boidIndex]() {boidIndex->SetText(std::to_string(simulation->getCurrFlock()->getCurrBoid()->getID() + 1)); };
	boidIndex->SetFunction(updateBoidIndex);
	UIElements.push_back(boidIndex);

	auto subB = [this]() {simulation->getCurrFlock()->setBoidIndexFrom(-1); };
	UIElements.push_back(new Button("B-", { 75, 140 }, { 70,90 }, subB));

	auto addB = [this]() {simulation->getCurrFlock()->setBoidIndexFrom(1); };
	UIElements.push_back(new Button("B+", { 215, 140 }, { 70,90 }, addB));

	//Toggle functions
	auto togHigOn = [this]() {simulation->getCurrFlock()->getCurrBoid()->setDrawHighlight(true); };
	auto togHigOff = [this]() {simulation->getCurrFlock()->getCurrBoid()->setDrawHighlight(false); };
	UIElements.push_back(new BToggle(" Highlight", { 20, 300 }, { 150,80 }, togHigOn, togHigOff));

	auto togNeiOn = [this]() {simulation->getCurrFlock()->getCurrBoid()->setDrawNear(true); };
	auto togNeiOff = [this]() {simulation->getCurrFlock()->getCurrBoid()->setDrawNear(false); };
	UIElements.push_back(new BToggle("Nearby", { 200, 300 }, { 150,80 }, togNeiOn, togNeiOff));

	auto togRanOn = [this]() {simulation->getCurrFlock()->getCurrBoid()->setDrawRange(true); };
	auto togRanOff = [this]() {simulation->getCurrFlock()->getCurrBoid()->setDrawRange(false); };
	UIElements.push_back(new BToggle("Range", { 20, 400 }, { 150,80 }, togRanOn, togRanOff));

	auto togTraOn = [this]() {simulation->getCurrFlock()->getCurrBoid()->setDrawTrail(true); };
	auto togTraOff = [this]() {simulation->getCurrFlock()->getCurrBoid()->setDrawTrail(false); };
	UIElements.push_back(new BToggle("Trail", { 200, 400 }, { 150,80 }, togTraOn, togTraOff));

	//Follow boid
	auto followB = [this]() {simulation->setFollowBoid(simulation->getCurrFlock()->getCurrBoid()); };
	auto unFollowB = [this]() {simulation->setDefaultView(); };
	UIElements.push_back(new BToggle("Follow", { 100, 700 }, { 150,70 }, followB, unFollowB));
}
