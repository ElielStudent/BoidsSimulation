#include "Game.h"

Game::Game() :window(sf::VideoMode(WIDTH, HEIGHT), "Boids work!"), menu(window),simulation(window) {
	window.setFramerateLimit(60);
	menu.setSimulation(&simulation);
}

void Game::Start() {
	sf::Clock fps;
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
		default:
			break;
		}
	}
}

void Game::Update() {
	menu.Update();
	simulation.Update();
}

void Game::Draw() {
	window.clear();
	simulation.Draw();
	menu.Draw();
	window.display();
}