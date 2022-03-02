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

void Flock::InsertBoids(QuadTree<Boid>* QT){
	for (Boid* b : boids)
		QT->Insert(b);
}

void Flock::UpdateBoids(QuadTree<Boid>* QT) {
	for (Boid* b : boids) {
		list<Boid*>* nearby = new list<Boid*>();
		QT->Query(b->getVisualRange(),nearby);
		b->Move(*nearby);
		delete nearby;
	}
}

void Flock::ClearFlock() {
	boids.clear();
}

void Flock::DrawFlock(sf::RenderWindow& window) {
	for (Boid* b : boids) {
		b->Draw(window);
	}
}

void Flock::setAlignment(float alignmentForce) {
	this->alignmentForce = alignmentForce;
	for (Boid* b : boids) {
		b->alignmentForce = alignmentForce;
	}
}

void Flock::setCohesion(float cohesionForce) {
	this->cohesionForce = cohesionForce;
	for (Boid* b : boids) {
		b->cohesionForce = cohesionForce;
	}
}

void Flock::setSeparation(float separationForce) {
	this->separationForce = separationForce;
	for (Boid* b : boids) {
		b->separationForce = separationForce;
	}
}
