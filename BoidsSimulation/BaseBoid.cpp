#include "BaseBoid.h"

BaseBoid::BaseBoid(float alignment, float cohesion, float separation,int id, int x, int y) {
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

	direction.x = float(cos((3.1415 / 180) * shape.getRotation()));
	direction.y = float(sin((3.1415 / 180) * shape.getRotation()));

	this->id = id;

	visualRange = BOIDSIGHT;
}

void BaseBoid::Move(std::list<BaseBoid*>& boids) {
	calcDirection(boids);

	this->shape.setRotation(atan2f(direction.x, -direction.y) * (180 / 3.1415));

	this->position += direction;
	this->shape.setPosition(this->position);
}

//Option to draw range, nearby boids
void BaseBoid::Draw(sf::RenderWindow& window) {
	
	window.draw(shape);
}

Vector2f BaseBoid::getPosition(){
	return position;
}

FloatRect BaseBoid::getVisualRange(){
	return FloatRect(position.x - visualRange, position.y - visualRange,
		visualRange*2,visualRange*2);
}

Vector2f BaseBoid::checkBounds() {
	Vector2f bound = { 0,0 };
	if (position.x > GWIDTH - BORDERSIZE) 
		bound.x -= TURNFACTOR;
	else if (position.x < BORDERSIZE) 
		bound.x += TURNFACTOR;
	if (position.y > GHEIGHT - BORDERSIZE) 
		bound.y -= TURNFACTOR;
	else if (position.y < BORDERSIZE) 
		bound.y += TURNFACTOR;
	return bound;
}

Vector2f BaseBoid::Alignment(std::list<BaseBoid*>& boids) {
	Vector2f align = { 0,0 };
	int total = 0;
	for (BaseBoid* b : boids) {
		if (!b->isVisible || b->id == this->id)
			continue;
		//double distance = abs(dist(b->position, position));
		//if (distance < visualRange) {
			align += b->direction;
			total++;
		//}
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

Vector2f BaseBoid::Cohesion(std::list<BaseBoid*>& boids)
{
	Vector2f cohesion = { 0,0 };
	int total = 0;
	for (BaseBoid* b : boids) {
		if (!b->isVisible || b->id == this->id)
			continue;
		//double distance = abs(dist(b->position, position));
		//if (distance < visualRange) {
			cohesion += b->position;
			total++;
		//}
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

Vector2f BaseBoid::Separation(std::list<BaseBoid*>& boids)
{
	Vector2f separation = { 0,0 };
	int total = 0;
	for (BaseBoid* b : boids) {
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
	separation -= direction;
	separation = limit(separation, MAXFORCE);
	return separation * separationForce;
}
