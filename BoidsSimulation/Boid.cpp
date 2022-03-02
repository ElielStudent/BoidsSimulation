#include "Boid.h"

void Boid::calcDirection(std::list<BaseBoid*>& boids){
	Vector2f newDirection = { 0,0 };
	if (changeSight) {
		if (boids.size() == 1) 			//Himself
			if (visualRange < MAXVISUALRANGE)
				visualRange *= 1.11;				//If it has no neighbors,increase range
			else {
				newDirection += Alignment(boids) + Cohesion(boids) + Separation(boids);
				visualRange *= 0.99;				//If it has neighbors, make its range smaller
			}
	}

	newDirection += checkBounds();
	direction += newDirection;
}
