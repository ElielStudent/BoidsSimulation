#include "PredatorBoid.h"

PredatorBoid::PredatorBoid(float alignment, float cohesion, float separation, int id, int flID, int x, int y,
	sf::Color fillColor, sf::Color outlineColor)
	:BaseBoid(id, flID, x, y, fillColor, outlineColor, alignment, cohesion, separation)
{
	boidType = BoidType::ePredatorBoid;
	shape.setScale(1.5, 2.25);
	chasingForce = CHASINGFORCE;
	visualRadius = MAXVISUALRANGE;
}

void PredatorBoid::calcDirection() {
	direction += ChaseBoid();
	if (!isChasing) {
		direction += Alignment() + Cohesion() + Separation();
		limitSpeed();
	}
	else {
		limitSpeed(MAXSPEED+10,MINSPEED+10);
	}
	direction += checkBounds();
}

sf::Vector2f PredatorBoid::ChaseBoid() {
	sf::Vector2f chaseV = { 0,0 };
	float total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible() || b->getBoidType() == ePredatorBoid || b->getFlID() == this->flID)
			continue;
		chaseV += b->getPosition();
		total++;
	}
	if (total == 0) {
		isChasing = false;
		return { 0,0 };
	}
	else
		isChasing = true;
	chaseV /= total;
	chaseV -= this->position;
	return chaseV * chasingForce;
}

//Alignment is based on visible boids in the same flock
sf::Vector2f PredatorBoid::Alignment() {
	sf::Vector2f align = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible() || b->getFlID() != this->flID)
			continue;
		align += b->getDirection();
		total++;
	}
	if (total == 0) return { 0,0 };
	align.x /= total;
	align.y /= total;
	align -= this->direction;
	return align * alignmentForce;
}

//Cohesion is based on visible boids in the same flock
sf::Vector2f PredatorBoid::Cohesion() {
	sf::Vector2f cohesion = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible() || b->getFlID() != this->flID)
			continue;
		cohesion += b->getPosition();
		total++;
	}
	if (total == 0) return { 0,0 };
	cohesion.x /= total;
	cohesion.y /= total;

	cohesion -= position;
	return cohesion * cohesionForce;
}

//Separation for predators doesnt separate them from boids of other flocks
sf::Vector2f PredatorBoid::Separation() {
	sf::Vector2f separation = { 0,0 };
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible() || b->getFlID() != this->flID)
			continue;
		float distance = abs(distSqrd(position, b->getPosition()));
		if (distance < SEPRANGE * SEPRANGE) {
			separation += position - b->getPosition();
		}
	}
	return separation * separationForce;
}
