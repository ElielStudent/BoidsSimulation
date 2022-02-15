#include "Game.h"

Game::Game() :window(sf::VideoMode(WIDTH, HEIGHT), "Boids work!") {
	window.setFramerateLimit(60);
}

void Game::Start() {
	menu.setSimulation(&simulation);
	while (window.isOpen()) {
		HandleEvents();
		Update();
		Draw();
	}
}

void Game::HandleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case(sf::Event::Closed):
			window.close();
			break;
		case(sf::Event::KeyPressed):
			simulation.addBoid();			//DELETE LATER
			break;
		case(sf::Event::MouseButtonPressed):
			menu.HandleButtons(sf::Mouse::getPosition(window));
			printf("x %d y %d\n", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			break;
		default:
			break;
		}
	}
}

void Game::Update(){
	simulation.Update();
}

void Game::Draw() {
	window.clear(Color::Cyan);
	simulation.Draw(window);
	menu.Draw(window);
	window.display();
}