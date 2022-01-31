#include "Boid.h"

Boid::Boid(float alignment, float cohesion, float separation,int id, int x, int y) {
	alignmentForce = alignment;
	cohesionForce = cohesion;
	separationForce = separation;
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color::Black);
	shape.setRadius(6);
	shape.setPointCount(3);
	shape.setScale(1, 1.5);

	position = Vector2f(x, y);
	shape.setPosition(position);
	shape.setRotation(rand() % 360);

	velocity.x = float(cos((3.1415 / 180) * shape.getRotation()));
	velocity.y = float(sin((3.1415 / 180) * shape.getRotation()));

	this->id = id;
}

void Boid::Move(std::list<Boid*>& boids) {
	velocity += checkBounds() + Alignment(boids) + Cohesion(boids) + Separation(boids);
	this->shape.setRotation(atan2f(velocity.x, -velocity.y) * (180 / 3.1415));

	this->position += velocity;
	this->shape.setPosition(this->position);
}

void Boid::Draw(sf::RenderWindow& window) {
	window.draw(shape);
}

Vector2f Boid::checkBounds() {
	Vector2f bound = { 0,0 };
	if (position.x > WIDTH - BORDERSIZE) 
		bound.x -= TURNFACTOR;
	else if (position.x < BORDERSIZE) 
		bound.x += TURNFACTOR;
	if (position.y > HEIGHT - BORDERSIZE) 
		bound.y -= TURNFACTOR;
	else if (position.y < BORDERSIZE) 
		bound.y += TURNFACTOR;
	return bound;
}

Vector2f Boid::Alignment(std::list<Boid*>& boids) {
	Vector2f align = { 0,0 };
	int total = 0;
	for (Boid* b : boids) {
		if (!b->isVisible || b->id == this->id)
			continue;
		double distance = abs(dist(b->position, position));
		if (distance < BOIDSIGHT) {
			align += b->velocity;
			total++;
		}
	}
	if (total == 0) return { 0,0 };
	align.x /= total;
	align.y /= total;
	align = normalize(align);
	align.x *= MAXSPEED;
	align.y *= MAXSPEED;
	align -= this->velocity;
	align = limit(align, MAXFORCE);
	return align * alignmentForce;
}

Vector2f Boid::Cohesion(std::list<Boid*>& boids)
{
	Vector2f cohesion = { 0,0 };
	int total = 0;
	for (Boid* b : boids) {
		if (!b->isVisible || b->id == this->id)
			continue;
		double distance = abs(dist(b->position, position));
		if (distance < BOIDSIGHT) {
			cohesion += b->position;
			total++;
		}
	}
	if (total == 0) return { 0,0 };
	cohesion.x /= total;
	cohesion.y /= total;
	cohesion -= position;
	cohesion = normalize(cohesion);
	cohesion.x *= MAXSPEED;
	cohesion.y *= MAXSPEED;
	cohesion -= velocity;
	cohesion = limit(cohesion, MAXFORCE);
    return cohesion * cohesionForce;
}

Vector2f Boid::Separation(std::list<Boid*>& boids)
{
	Vector2f separation = { 0,0 };
	int total = 0;
	for (Boid* b : boids) {
		if (!b->isVisible || b->id == this->id)
			continue;
		float distance = abs(dist(position, b->position));
		if (distance < SEPRANGE) {
			Vector2f difference = position - b->position;
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
	separation -= velocity;
	separation = limit(separation, MAXFORCE);
	return separation * separationForce;
}
