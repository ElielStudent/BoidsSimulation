#include "Boid.h"

Boid::Boid(float alignment, float cohesion, float separation, int id, int flID, int x, int y,
	sf::Color fillColor, sf::Color outlineColor)
	:BaseBoid(id, flID, x, y, fillColor, outlineColor, alignment, cohesion, separation)
{
	boidType = BoidType::eNormalBoid;
	escapeForce = ESCAPEFORCE;
}

void Boid::calcDirection() {
	if (changeSight) {
		if (localBoids->size() == 0) { 				//If no boids are around
			if (visualRadius < MAXVISUALRANGE)
				visualRadius *= 1.004f;				//If it has no neighbors,increase range
		}
		else {
			if (visualRadius > MINVISUALRANGE)
				visualRadius *= 0.9995f;				//If it has neighbors, make its range smaller
		}
	}
	direction += Escape();
	if (!isEscaping) {
		direction += Alignment() + Cohesion() + Separation();
	}
	limitSpeed();
	direction += checkBounds();
}

sf::Vector2f Boid::Escape() {
	sf::Vector2f escapeV = { 0,0 };
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible() || b->getBoidType() != BoidType::ePredatorBoid || b->getFlID() == this->flID)
			continue;
		if (this->shape.getGlobalBounds().intersects(b->getShapeGlobalBounds())) {
			this->isdead = true;
			return { 0,0 };
		}
		escapeV += position - b->getPosition();
	}
	if (escapeV.x != 0 && escapeV.y != 0)
		isEscaping = true;
	else
		isEscaping = false;
	return escapeV * escapeForce;
}