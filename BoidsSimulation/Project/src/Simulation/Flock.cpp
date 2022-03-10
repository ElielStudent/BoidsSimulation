#include "Flock.h"

Flock::Flock(int flID) {
	alignmentForce = ALIGNMENT;
	cohesionForce = COHESION;
	separationForce = SEPARATION;
	this->flID = flID;
	boids.push_back(new UserBoid(++fCount,this->flID));
}

void Flock::AddBoid() {
	Boid* boid = new Boid(alignmentForce, cohesionForce, separationForce, ++fCount,this->flID);
	boids.push_back(boid);
}

void Flock::AddBoid(int x, int y) {
	Boid* boid = new Boid(alignmentForce, cohesionForce, separationForce, ++fCount, x, y);
	boids.push_back(boid);
}

void Flock::InsertBoids(QuadTree<BaseBoid>* QT) {
	for (BaseBoid* b : boids)
		QT->Insert(b);
}

void Flock::UpdateBoids(QuadTree<BaseBoid>* QT) {
	for (BaseBoid* b : boids) {
		std::list<BaseBoid*>* nearby = new std::list<BaseBoid*>();
		//DOUBLE RANGE???????
		//QT->Query(b->getVisualBoundary(),nearby);						//Square range
		QT->Query(b->getPosition(), b->getVisualRange(), nearby);		//Radius based	(doesn't return himself)
		b->setNeighborBoids(nearby);
		b->Move();
	}
}

void Flock::ClearFlock() {
	boids.clear();
}

void Flock::DrawFlock(sf::RenderWindow& window) {
	for (BaseBoid* b : boids) {
		b->Draw(window);

	}
}

BaseBoid* Flock::GetBoid(int id) {
	if (id > boids.size()) return nullptr;
	std::list<BaseBoid*>::iterator it = this->boids.begin();
	std::advance(it, id - 1);
	return *it;
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
