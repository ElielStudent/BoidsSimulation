#include "Boid.h"

Boid::Boid(float alignment, float cohesion, float separation, int id, int flID, int x, int y,
	sf::Color fillColor, sf::Color outlineColor)
	:BaseBoid(id, flID, x, y, fillColor, outlineColor,alignment,cohesion,separation)
{
	boidType = BoidType::eNormalBoid;
	escapeForce = ESCAPEFORCE;
}

void Boid::calcDirection() {
	sf::Vector2f newDirection = { 0,0 };
	if (changeSight) {
		if (localBoids->size() == 0) { 				//If no boids are around
			if (visualRadius < MAXVISUALRANGE)
				visualRadius *= 1.01f;				//If it has no neighbors,increase range
		}
		else {
			newDirection = Alignment() + Cohesion() + Separation() + Escape();
			if (visualRadius > MINVISUALRANGE)
				visualRadius *= 0.985f;				//If it has neighbors, make its range smaller
		}
	}
	newDirection += checkBounds();
	direction += newDirection;
}

sf::Vector2f Boid::Escape() {
	sf::Vector2f escapeV = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible() || b->getID() == this->id || b->getBoidType() != BoidType::ePredatorBoid)
			continue;
		float distance = abs(dist(position, b->getPosition()));
		if (distance < SEPRANGE) {
			sf::Vector2f difference = position - b->getPosition();
			difference = normalize(difference);
			difference /= distance;
			escapeV += difference;
			total++;
		}
	}
	if (total == 0) return { 0,0 };
	escapeV.x /= total;
	escapeV.y /= total;
	escapeV = normalize(escapeV);
	escapeV.x *= MAXSPEED;
	escapeV.y *= MAXSPEED;
	escapeV -= direction;
	escapeV = limit(escapeV, MAXFORCE);
	return escapeV * escapeForce;
}