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

