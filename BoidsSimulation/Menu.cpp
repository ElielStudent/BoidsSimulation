#include "Menu.h"

Menu::Menu() {
	MenuV.setCenter(MWIDTH / 2, MHEIGHT / 2);
	MenuV.setSize(MWIDTH, MHEIGHT);
	MenuV.setViewport(FloatRect(0, 0, MWIDTHPer, 1.f));
	simulation = nullptr;
	LoadButtons();
}

void Menu::setSimulation(Simulation* simulation){
	this->simulation = simulation;
}

void Menu::Draw(RenderWindow& window) {
	window.setView(MenuV);
	//Draw background
	for (Button b : buttons) {
		b.draw(window);
	}
}

void Menu::LoadButtons() {
	auto szout = [this]() {simulation->changeSize({ 30,30 }); };
	auto szin = [this]() {simulation->changeSize({ -30,-30 }); };

	sZoomIn.setText("S+");
	sZoomIn.setPosition({ 60 ,GHEIGHT - 100 });
	sZoomIn.setFunction(szin);
	buttons[0] = sZoomIn;

	sZoomOut.setText("S -");
	sZoomOut.setPosition({ 60,GHEIGHT - 200 });
	sZoomOut.setFunction(szout);
	buttons[1] = sZoomOut;

	auto wzout = [this]() {simulation->getWorld()->changeSize({ 30,30 }); };
	auto wzin = [this]() {simulation->getWorld()->changeSize({ -30,-30 }); };

	wZoomIn.setText("W +");
	wZoomIn.setPosition({ 60 ,GHEIGHT - 300 });
	wZoomIn.setFunction(wzin);
	buttons[2] = wZoomIn;

	wZoomOut.setText("W-");
	wZoomOut.setPosition({ 60,GHEIGHT - 400 });
	wZoomOut.setFunction(wzout);
	buttons[3] = wZoomOut;

	auto quadToggle = [this]() {simulation->toggleDrawQuad(); };
	qtToggle.setText("QT +");
	qtToggle.setPosition({ 60 ,GHEIGHT - 500 });
	qtToggle.setFunction(quadToggle);
	buttons[4] = qtToggle;
}

void Menu::HandleButtons(Vector2i mousePos) {		//Mouse relative to the window
	//Handle differnet button presses, loop through list checking each one
	for (Button b : buttons) {
		b.checkClick(mousePos);
	}
}