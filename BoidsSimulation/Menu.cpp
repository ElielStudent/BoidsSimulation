#include "Menu.h"

Menu::Menu() {
	MenuV.setCenter(MWIDTH / 2, MHEIGHT / 2);
	MenuV.setSize(MWIDTH, MHEIGHT);
	MenuV.setViewport(FloatRect(0, 0, MWIDTHPer, 1.f));
	simulation = nullptr;
	LoadButtons();
}

void Menu::Update(RenderWindow& window) {
	for (UIElement* ui : UIElements) {
		ui->Update(window);
	}
}

void Menu::setSimulation(Simulation* simulation) {
	this->simulation = simulation;
}

void Menu::Draw(RenderWindow& window) {
	window.setView(MenuV);
	//Draw background
	for (UIElement* element : UIElements) {
		element->Draw(window);
	}
}

void Menu::LoadButtons() {
	auto szout = [this]() {simulation->changeSize({ 30,30 }); };
	auto szin = [this]() {simulation->changeSize({ -30,-30 }); };

	Button* sZoomIn = new Button("S +", { 60,GHEIGHT - 100 }, { 100, 50 }, szin);
	UIElements.push_back(sZoomIn);

	Button* sZoomOut = new Button("S -", { 60,GHEIGHT - 200 }, { 100,50 }, szout);
	UIElements.push_back(sZoomOut);

	auto wzout = [this]() {simulation->getWorld()->changeSize({ 30,30 }); };
	auto wzin = [this]() {simulation->getWorld()->changeSize({ -30,-30 }); };

	Button* wZoomIn = new Button("W +", { 60,GHEIGHT - 300 }, { 100,50 }, wzin);
	UIElements.push_back(wZoomIn);

	Button* wZoomOut = new Button("W -", { 60,GHEIGHT - 400 }, { 100,50 }, wzout);
	UIElements.push_back(wZoomOut);

	auto quadToggle = [this]() {simulation->toggleDrawQuad(); };
	Button* qtToggle = new Button("QT +", { 60,GHEIGHT - 500 }, { 100,50 }, quadToggle);
	UIElements.push_back(qtToggle);

}
