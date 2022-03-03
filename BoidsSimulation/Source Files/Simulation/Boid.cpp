#include "Boid.h"

Boid::Boid(float alignment, float cohesion, float separation, int id, int x, int y)
	:BaseBoid(id, x, y) 
{
	alignmentForce = alignment;
	cohesionForce = cohesion;
	separationForce = separation;
	boidType = eNormalBoid;
	escapeForce = 5;
}

void Boid::calcDirection() {
	Vector2f newDirection = { 0,0 };
	if (changeSight) {
		if (localBoids->size() == 1) { 			//Himself
			if (visualRange < MAXVISUALRANGE)
				visualRange *= 1.01;				//If it has no neighbors,increase range
		}
		else {
			newDirection += Alignment() + Cohesion() + Separation() + Escape();
			if (visualRange > MINVISUALRANGE)
				visualRange *= 0.985;				//If it has neighbors, make its range smaller
		}
	}
	newDirection += checkBounds();
	direction += newDirection;
}


Vector2f Boid::Alignment() {
	Vector2f align = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible || b->id == this->id || b->boidType != eNormalBoid)
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

Vector2f Boid::Cohesion()
{
	Vector2f cohesion = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible || b->id == this->id || b->boidType != eNormalBoid)
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

Vector2f Boid::Separation()
{
	Vector2f separation = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible || b->id == this->id || b->boidType != eNormalBoid)
			continue;
		float distance = abs(dist(position, b->getPosition()));
		if (distance < SEPRANGE) {
			Vector2f difference = position - b->getPosition();
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

Vector2f Boid::Escape() {
	Vector2f escapeV = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible || b->id == this->id || b->boidType != ePredatorBoid)
			continue;
		float distance = abs(dist(position, b->getPosition()));
		if (distance < SEPRANGE) {
			Vector2f difference = position - b->getPosition();
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