#include "Simulation.h"

Simulation::Simulation(sf::RenderWindow& window) :window(window) {
	world = new World();
	currFlock = nullptr;
	SimulationV.setCenter(GWIDTH / 2, GHEIGHT / 2);
	SimulationV.setSize(GWIDTH, GHEIGHT);
	SimulationV.setViewport(sf::FloatRect(MWIDTHPer, 0, GWIDTHPer, 1.f));
	QT = new QuadTree<BaseBoid>();
	AddFlock();
}

Flock* Simulation::getFlock(int id) {
	if (id > flocks.size()) return nullptr;
	std::list<Flock*>::iterator it = flocks.begin();
	std::advance(it, id - 1);
	return *it;
}

void Simulation::UpdateQuadTree() {
	QT->Clear();
	for (Flock* f : flocks)
		f->InsertBoids(QT);			//Adds the boids of each flock into the global QT
}

void Simulation::AddFlock() {
	if (this->flocks.size() < 15) {
		flocks.push_back(new Flock(flocks.size(),window));
		currFlock = flocks.back();
		currFlockIndex = flocks.size() - 1;
		boidPopulation++;
	}
}

void Simulation::AddBoid(BoidType boidType) {
	boidPopulation++;
	currFlock->AddBoid(boidType);
}

void Simulation::Draw() {
	if (followBoid != nullptr) {
		sf::Vector2f followPos = followBoid->getPosition();
		world->setView(followPos);
		SimulationV.setCenter(followPos);
		SimulationV.setSize(GWIDTH / 2, GHEIGHT / 2);
	}

	world->drawWorld(window);

	window.setView(SimulationV);
	if (drawQuad)	//option to draw quadtree
		QT->Draw(window);

	DrawPopulation();

	for (Flock* f : flocks) {
		f->DrawFlock(window);
	}
}

void Simulation::DrawPopulation() {
	sf::Font font;
	font.loadFromFile("Arial.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString(std::to_string(boidPopulation));
	text.setPosition(GWIDTH - 50, GHEIGHT - 50);
	text.setFillColor(sf::Color(120, 120, 120));
	window.draw(text);
}

void Simulation::Update() {
	window.setView(SimulationV);
	UpdateQuadTree();
	boidPopulation = 0;
	for (Flock* f : flocks) {
		f->UpdateBoids(QT);
		boidPopulation += f->getBoidCount();
	}
}


void Simulation::changeSize(sf::Vector2f size) {
	SimulationV.setSize(SimulationV.getSize() + size);
	std::cout << "Simulation: " << SimulationV.getSize().x << " " << SimulationV.getSize().y << std::endl;
}

World* Simulation::getWorld() {
	return world;
}

void Simulation::toggleDrawQuad() {
	drawQuad = !drawQuad;
}

void Simulation::setDrawQuad(bool state) {
	drawQuad = state;
}

void Simulation::setDefaultView() {
	followBoid = nullptr;
	SimulationV.setCenter(GWIDTH / 2, GHEIGHT / 2);
	SimulationV.setSize(GWIDTH, GHEIGHT);
	world->setDefaultView();
}

void Simulation::setFollowBoid(BaseBoid* boid) {
	followBoid = boid;
}

int Simulation::setFlockIndexFrom(int num) {
	int flockCount = flocks.size();
	num = ((num + currFlockIndex) + flockCount) % flockCount;
	std::list<Flock*>::iterator it = flocks.begin();
	std::advance(it, num);
	currFlock = *it;
	currFlockIndex = (*it)->getFLID();
	return currFlockIndex;
}

void Simulation::resetSim() {
	for (Flock* f : flocks) {
		f->ClearFlock();
		delete f;
	}
	flocks.clear();
	world->ReGenerateWorld();
	AddFlock();
}
