#include "Game.h"

Game::Game() :window(sf::VideoMode(GWIDTH, GHEIGHT), "Boids work!") {
	window.setFramerateLimit(60);
}

void Game::Start() {
	LoadGame();
	while (window.isOpen()) {
		HandleEvents();
		Update();
		Draw();
	}
}

void Game::AddFlock() {
	Flock* flock = new Flock(++flockCount);
	++currFlock;
	flocks.push_back(*flock);
}

void Game::LoadGame() {
	LoadViews();
	AddFlock();
	LoadButtons();
}

void Game::LoadButtons() {
	bSeparation.setText("Separate " + std::to_string(SEPARATION));
	bSeparation.setLocation({ GHEIGHT - 20,GWIDTH - 30 });
}

void Game::LoadViews() {
	SimulationV.setCenter(GWIDTH / 2, GHEIGHT / 2);
	SimulationV.setSize(GWIDTH, GHEIGHT);
	SimulationV.setViewport(FloatRect(MWIDTHPer, 0, GWIDTHPer, 1.f));
	MenuV.setCenter(MWIDTH / 2, MHEIGHT / 2);
	MenuV.setSize(MWIDTH, MHEIGHT);
	MenuV.setViewport(FloatRect(0, 0, MWIDTHPer, 1.f));
	WorldV.setCenter(WORLDSIZE / 2, WORLDSIZE / 2);				//What the view is centered in
	WorldV.setSize(WORLDSIZE / 2, WORLDSIZE / 2);						//What the view can see	(the screen size/2)
	WorldV.setViewport(FloatRect(MWIDTHPer, 0, GWIDTHPer, 1.f));	//Top,left,width,height of the viewport
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

void Game::HandleButtons(Vector2i mousePos) {		//Mouse relative to the window
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
	window.clear();
	DrawGame();	
	DrawMenu();
	window.display();
}

void Game::DrawMenu(){
	window.setView(MenuV);
	//window.clear(Color::Red);
}

void Game::DrawGame(){
	window.setView(WorldV);
	//window.clear({ 135, 206, 235 });

	world.drawWorld(window);

	window.setView(SimulationV);
	for (Flock f : flocks) {
		f.DrawFlock(window);
	}
	//option to draw quadtree
	window.setView(MenuV);
	for (Button b : buttons) {
		b.draw(window);
	}

}
