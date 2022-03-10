#include "Boid.h"

Boid::Boid(float alignment, float cohesion, float separation, int id,int flID, int x, int y)
	:BaseBoid(id,flID, x, y) 
{
	alignmentForce = alignment;
	cohesionForce = cohesion;
	separationForce = separation;
	boidType = BoidType::eNormalBoid;
	escapeForce = 5;
}

void Boid::calcDirection() {
	sf::Vector2f newDirection = { 0,0 };
	if (changeSight) {
		if (localBoids->size() == 0) { 				//If no boids are around
			if (visualRadius < MAXVISUALRANGE)
				visualRadius *= 1.01f;				//If it has no neighbors,increase range
		}
		else {
			newDirection += Alignment() + Cohesion() + Separation() + Escape();
			if (visualRadius > MINVISUALRANGE)
				visualRadius *= 0.985f;				//If it has neighbors, make its range smaller
		}
	}
	newDirection += checkBounds();
	direction += newDirection;
}

//Alignment is based on visible boids in the same flock
sf::Vector2f Boid::Alignment() {
	sf::Vector2f align = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible || b->id == this->id || b->boidType == BoidType::ePredatorBoid)
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

//Cohesion is based on visible boids in the same flock
sf::Vector2f Boid::Cohesion()
{
	sf::Vector2f cohesion = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible || b->id == this->id || b->boidType == BoidType::ePredatorBoid)
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

//Separation is based on visible non-predator boids
sf::Vector2f Boid::Separation()
{
	sf::Vector2f separation = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible || b->id == this->id || b->boidType == BoidType::ePredatorBoid)	//Follows all but predator
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

sf::Vector2f Boid::Escape() {
	sf::Vector2f escapeV = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible || b->id == this->id || b->boidType != BoidType::ePredatorBoid)
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