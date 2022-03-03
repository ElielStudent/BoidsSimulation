#include "PredatorBoid.h"

PredatorBoid::PredatorBoid( int id, int x, int y)
	:BaseBoid(id,x,y)
{
	boidType = ePredatorBoid;
}

void PredatorBoid::calcDirection() {
	Vector2f newDirection = { 0,0 };
	if (changeSight) {
		if (localBoids->size() == 1) { 			//Himself
			if (visualRange < MAXVISUALRANGE)
				visualRange *= 1.01;				//If it has no neighbors,increase range
		}
		else {
			newDirection += ChaseBoid();
			if (visualRange > MINVISUALRANGE)
				visualRange *= 0.985;				//If it has neighbors, make its range smaller
		}
	}

	newDirection += checkBounds();
	direction += newDirection;
	limit(direction, 5);

}

Vector2f PredatorBoid::ChaseBoid(){
	Vector2f chaseV = { 0,0 };
	float total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible)
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

