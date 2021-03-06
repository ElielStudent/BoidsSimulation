#include "Flock.h"

Flock::Flock(int flID, sf::RenderWindow& window) :window(window) {
	alignmentForce = ALIGNMENT;
	cohesionForce = COHESION;
	separationForce = SEPARATION;
	this->flID = flID;
	this->color = sf::Color((rand() % (255 - 64)) + 64, (rand() % (255 - 64)) + 64, (rand() % (255 - 64)) + 64);
	AddBoid(eNormalBoid);
	currBoid = boids.front();
	currBoidIndex = currBoid->getID();
}

void Flock::AddBoid(BoidType bType) {
	BaseBoid* boid;
	switch (bType) {
	case(eNormalBoid):
		boid = new Boid(alignmentForce, cohesionForce, separationForce, fCount++, this->flID);
		break;
	case(eUserBoid):
		boid = new UserBoid(fCount++, this->flID);
		break;
	case(ePredatorBoid):
		boid = new PredatorBoid(alignmentForce, cohesionForce, separationForce, fCount++, this->flID);
		break;
		/*case(eAiBoid):
			break;*/
	default:
		boid = new Boid(alignmentForce, cohesionForce, separationForce, fCount++, this->flID);
		break;
	}
	boid->setColor(this->color);
	boids.push_back(boid);
}

void Flock::InsertBoids(QuadTree<BaseBoid>* QT) {
	for (BaseBoid* b : boids)
		QT->Insert(b);
}

void Flock::UpdateBoids(QuadTree<BaseBoid>* QT) {
	std::list<BaseBoid*>::iterator it = boids.begin();
	while (it != boids.end()) {
		BaseBoid* b = (*it);
		if (b->isDead()) {
			b->setNeighborBoids(nullptr);	//Delete the pointer to the nearby list of the boid
			delete b;						//Delete the boid
			it = boids.erase(it);			//Erase from list and update the iterator
			fCount--;
			continue;
		}
		std::list<BaseBoid*>* nearby = new std::list<BaseBoid*>();
		//QT->Query(b->getVisualBoundary(),nearby);						//Square range
		QT->Query(b->getPosition(), b->getVisualRange(), nearby);		//Radius based	(doesn't return himself)
		b->setNeighborBoids(nearby);									//Set nearby boids of the boid
		if (b->isFollowingMouse())
			b->Move(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		else
			b->Move();														//Update the boid
		it++;															//Keep iterating
	}
}

void Flock::ClearFlock() {
	for (BaseBoid* b : boids)
		delete b;
	boids.clear();
	currBoid = nullptr;
}

void Flock::RestartFlock() {
	this->ClearFlock();
	fCount = 0;
	this->AddBoid(eBaseBoid);
	currBoid = boids.front();
	currBoidIndex = currBoid->getID();
}

void Flock::DrawFlock(sf::RenderWindow& window) {
	for (BaseBoid* b : boids) {
		b->Draw(window);
	}
}

BaseBoid* Flock::getBoid(int id) {
	if (id > boids.size()) return nullptr;
	std::list<BaseBoid*>::iterator it = this->boids.begin();
	std::advance(it, id - 1);
	return *it;
}

int Flock::getBoidCount() {
	return fCount;
}

void Flock::setAlignment(float alignmentForce) {
	this->alignmentForce = alignmentForce;
	for (BaseBoid* b : boids) {
		b->setAlignment(alignmentForce);
	}
}

void Flock::setCohesion(float cohesionForce) {
	this->cohesionForce = cohesionForce;
	for (BaseBoid* b : boids) {
		b->setCohesion(cohesionForce);
	}
}

void Flock::setSeparation(float separationForce) {
	this->separationForce = separationForce;
	for (BaseBoid* b : boids) {
		b->setSeparation(separationForce);
	}
}

void Flock::setMouseFollow(bool state) {
	for (BaseBoid* b : boids)
		b->setMouseFollow(state);
}

void Flock::setDrawRange(bool state) {
	for (BaseBoid* b : boids)
		b->setDrawRange(state);
}

void Flock::setDrawNear(bool state) {
	for (BaseBoid* b : boids)
		b->setDrawNear(state);
}

void Flock::setDrawTrail(bool state) {
	for (BaseBoid* b : boids)
		b->setDrawTrail(state);
}

void Flock::setDrawHighlight(bool state) {
	for (BaseBoid* b : boids)
		b->setDrawHighlight(state);
}

int Flock::setBoidIndexFrom(int num) {
	int boidCount = boids.size();
	int index = ((num + currBoidIndex) + boidCount) % boidCount;
	std::list<BaseBoid*>::iterator it = boids.begin();
	std::advance(it, index);
	currBoid = *it;
	currBoidIndex = (*it)->getID();
	return currBoidIndex;
}

