#include "Game.h"

Game::Game() :window(sf::VideoMode(WIDTH, HEIGHT), "Boids work!") {
	window.setFramerateLimit(60);
}

void Game::Start(){
	LoadGame();
	while (window.isOpen()) {
		HandleEvents();
		Update();
		Draw();
	}
}

void Game::AddFlock(){
	Flock* flock = new Flock(++flockCount);
	++currFlock;
	flocks.push_back(*flock);
}

void Game::LoadGame(){
	LoadViews();
	AddFlock();
	LoadButtons();
}

void Game::LoadButtons() {
	bSeparation.setText("Separate " + std::to_string(SEPARATION));
	bSeparation.setLocation({ HEIGHT - 20,WIDTH - 30 });
}

void Game::LoadViews() {
	//SimulationV.setCenter();
}

void Game::HandleEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case(sf::Event::Closed):
			window.close();
			break;
		case(sf::Event::KeyPressed):
			flocks.front().AddBoid();			//DELETE LATER
			break;
		case(sf::Event::MouseButtonPressed):
			HandleButtons(sf::Mouse::getPosition(window));
		default:
			break;
		}
	}
}

void Game::HandleButtons(Vector2i mousePos){		//Mouse relative to the window
	//Handle differnet button presses, loop through list checking each one
}

void Game::Update() {
	for (Flock f : flocks) {
		f.UpdateBoids(QT);
	}
	//call flock to move boids and check death,etc

	//for all flocks
	//for all boids in flock
	//add to quadtree and recalculate it
}

void Game::Draw() {
	window.clear({ 135, 206, 235 });
	window.setView(SimulationV);
	for (Flock f : flocks) {
		f.DrawFlock(window);
	}
	//option to draw quadtree
	window.setView(MenuV);
	for (Button b : buttons) {
		b.draw(window);
	}

	window.display();
}
