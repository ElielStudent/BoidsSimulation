#include "PredatorBoid.h"

PredatorBoid::PredatorBoid(float alignment, float cohesion, float separation, int id,int flID, int x, int y,
	sf::Color fillColor, sf::Color outlineColor)
	:BaseBoid(id,flID, x, y,fillColor,outlineColor,alignment,cohesion,separation)
{
	boidType = BoidType::ePredatorBoid;
}

void PredatorBoid::calcDirection() {
	sf::Vector2f newDirection = { 0,0 };
	if (changeSight) {
		if (localBoids->size() == 0) { 				//If no other boids are around
			if (visualRadius < MAXVISUALRANGE)
				visualRadius *= 1.01f;				//If it has no neighbors,increase range
		}
		else {
			newDirection += ChaseBoid();
			if (visualRadius > MINVISUALRANGE)
				visualRadius *= 0.985f;				//If it has neighbors, make its range smaller
		}
	}

	newDirection += checkBounds();
	direction += newDirection;
	limit(direction, 5);

}

sf::Vector2f PredatorBoid::Alignment() {
	sf::Vector2f align = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible() || b->getID() == this->id|| b->getFlID() != this->flID)
			continue;
		align += b->getDirection();
		total++;
	}
	if (total == 0) return { 0,0 };
	align.x /= total;
	align.y /= total;
	align = normalize(align);
	align.x *= MAXSPEED;
	align.y *= MAXSPEED;
	align -= this->direction;
	align = limit(align, MAXFORCE);
	return align * alignmentForce;
}

sf::Vector2f PredatorBoid::Cohesion() {
	sf::Vector2f cohesion = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible() || b->getID() == this->id || b->getFlID() != this->flID)
			continue;
		cohesion += b->getPosition();
		total++;
	}
	if (total == 0) return { 0,0 };
	cohesion.x /= total;
	cohesion.y /= total;
	cohesion -= position;
	cohesion = normalize(cohesion);
	cohesion.x *= MAXSPEED;
	cohesion.y *= MAXSPEED;
	cohesion -= direction;
	cohesion = limit(cohesion, MAXFORCE);
	return cohesion * cohesionForce;
}

sf::Vector2f PredatorBoid::Separation() {
	sf::Vector2f separation = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible() || b->getID() == this->id || b->getFlID() != this->flID)
			continue;
		float distance = abs(dist(position, b->getPosition()));
		if (distance < SEPRANGE) {
			sf::Vector2f difference = position - b->getPosition();
			difference = normalize(difference);
			difference /= distance;
			separation += difference;
			total++;
		}
	}
	if (total == 0) return { 0,0 };
	separation.x /= total;
	separation.y /= total;
	separation = normalize(separation);
	separation.x *= MAXSPEED;
	separation.y *= MAXSPEED;
	separation -= direction;
	separation = limit(separation, MAXFORCE);
	return separation * separationForce;
}

sf::Vector2f PredatorBoid::ChaseBoid() {
	sf::Vector2f chaseV = { 0,0 };
	float total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible())
			continue;
		chaseV += b->getPosition();
		total++;
	}
	if (total == 0) return { 0,0 };
	chaseV /= total;
	chaseV -= this->position;
	//chaseV /= chasingForce;				//Moves the boid chasingForce% of the way towards the boids at each step
	chaseV = normalize(chaseV);
	chaseV.x *= MAXSPEED;
	chaseV.y *= MAXSPEED;
	chaseV -= direction;
	chaseV = limit(chaseV, MAXFORCE);
	return chaseV * chasingForce;
}

