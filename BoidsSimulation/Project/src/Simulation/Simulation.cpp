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
		f->InsertBoids(QT);
}

void Simulation::AddFlock() {
	flocks.push_back(new Flock(flocks.size()));
	currFlock = flocks.back();
	currFlockIndex = flocks.size() - 1;
}

void Simulation::AddBoid() {			//TEMPORARY, FIX TO MAKE BETTER LOL
	if (currFlock == nullptr)AddFlock();
	currFlock->AddBoid(eBaseBoid);
}

void Simulation::Draw() {
	world->drawWorld(window);

	window.setView(SimulationV);
	if (drawQuad)	//option to draw quadtree
		QT->Draw(window);

	for (Flock* f : flocks) {
		f->DrawFlock(window);
	}
}

void Simulation::Update() {
	UpdateQuadTree();

	for (Flock* f : flocks) {
		f->UpdateBoids(QT);
	}
}

void Simulation::Zoom(float zAmount) {

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

void Simulation::setDrawQuad(bool state){
	drawQuad = state;
}

int Simulation::setFlockIndexFrom(int num) {
	int flockCount = flocks.size();
	num = ((num + currFlockIndex) + flockCount) % flockCount;
	std::list<Flock*>::iterator it = flocks.begin();
	std::advance(it, num);
	currFlock = *it;
	currFlockIndex = (*it)->getFLID();
	return num;
}
