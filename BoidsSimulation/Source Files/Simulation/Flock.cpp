#include "Flock.h"

Flock::Flock(int id) {
	alignmentForce = ALIGNMENT;
	cohesionForce = COHESION;
	separationForce = SEPARATION;
	this->id = id;
}

void Flock::AddBoid() {
	Boid* boid = new Boid(alignmentForce, cohesionForce, separationForce, ++fCount);
	boids.push_back(boid);
}

void Flock::AddBoid(int x, int y) {
	Boid* boid = new Boid(alignmentForce, cohesionForce, separationForce, ++fCount, x, y);
	boids.push_back(boid);
}

void Flock::InsertBoids(QuadTree<BaseBoid>* QT){
	for (BaseBoid* b : boids)
		QT->Insert(b);
}

void Flock::UpdateBoids(QuadTree<BaseBoid>* QT) {
	for (BaseBoid* b : boids) {
		list<BaseBoid*>* nearby = new list<BaseBoid*>();
		QT->Query(b->getVisualRange(),nearby);
		b->setNeighborBoids(nearby);
		b->Move();
	}
}

void Flock::ClearFlock() {
	boids.clear();
}

void Flock::DrawFlock(sf::RenderWindow& window) {
	for (BaseBoid* b : boids) {
		if (b->drawRange)
			b->DrawVisualRange(window);
		//Option to draw nearby boids
		if (b->drawNeighbors)
			b->DrawNeighbors(window);
		b->Draw(window);

	}
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
