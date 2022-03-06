#include "Game.h"

Game::Game() :window(sf::VideoMode(WIDTH, HEIGHT), "Boids work!") {
	window.setFramerateLimit(60);
	menu.setSimulation(&simulation);
}

void Game::Start() {
	Clock fps;
	float lastTime = 0;
	while (window.isOpen()) {
		HandleEvents();
		Update();
		Draw();
		float currTime = fps.restart().asSeconds();
		printf("%f \n", 1.f / currTime);
		lastTime = currTime;
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
			//menu.HandleButtons(sf::Mouse::getPosition(window));
			//printf("x %d y %d\n", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			break;
		default:
			break;
		}
	}
}

void Game::Update(){
	menu.Update(window);
	simulation.Update();
}

void Game::Draw() {
	window.clear();
	simulation.Draw(window);
	menu.Draw(window);
	window.display();
}