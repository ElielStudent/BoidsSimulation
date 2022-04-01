#include "BaseBoid.h"
#include "..\..\include\BaseBoid.h"

BaseBoid::BaseBoid(int id, int flID, int x, int y, sf::Color fillColor, sf::Color outlineColor,
	float alignment, float cohesion, float separation) {
	shape.setFillColor(fillColor);
	shape.setOutlineThickness(1);
	shape.setOutlineColor(outlineColor);
	shape.setRadius(BOIDRADIUS);
	shape.setPointCount(3);
	shape.setOrigin(BOIDRADIUS / 2, BOIDRADIUS / 2);
	shape.setScale(1, 1.5);

	position = sf::Vector2f(x, y);
	shape.setPosition(position);
	shape.setRotation(rand() % 360);

	direction.x = float(cos((3.1415 / 180) * shape.getRotation()));
	direction.y = float(sin((3.1415 / 180) * shape.getRotation()));
	direction = normalize(direction);
	direction.x *= MAXSPEED;
	direction.y *= MAXSPEED;

	this->alignmentForce = alignment;
	this->cohesionForce = cohesion;
	this->separationForce = separation;

	visualRadius = BOIDSIGHT;

	this->id = id;
	this->flID = flID;

	localBoids = nullptr;

	for (int i = 0; i < TRAILSIZE; i++)		//Init the lastPos 
		lastPos.push_back({ 0,0 });
}

void BaseBoid::Move() {
	calcDirection();

	this->shape.setRotation(atan2f(direction.x, -direction.y) * (180 / 3.1415f));

	this->position += direction;

	lastPos.push_front(position);
	lastPos.pop_back();
	this->shape.setPosition(this->position);
}

void BaseBoid::setNeighborBoids(std::list<BaseBoid*>* localBoids) {
	delete this->localBoids;
	this->localBoids = localBoids;
}

//Option to draw range, nearby boids
void BaseBoid::Draw(sf::RenderWindow& window) {
	if (this->drawRange)
		DrawVisualRange(window);
	if (this->drawNear)
		DrawNear(window);
	if (this->drawTrail)
		DrawTrail(window);
	if (this->drawHighlight)
		DrawHighlight(window);
	window.draw(shape);
}

void BaseBoid::setColor(sf::Color fillColor, sf::Color outlineColor) {
	shape.setFillColor(fillColor);
	shape.setOutlineColor(outlineColor);
}

void BaseBoid::DrawVisualRange(sf::RenderWindow& window) {
	sf::CircleShape range;
	range.setRadius(this->visualRadius);
	range.setPosition({ this->position.x - this->visualRadius  ,
		this->position.y - this->visualRadius });
	range.setFillColor(sf::Color::Transparent);
	range.setOutlineColor(sf::Color::White);
	range.setOutlineThickness(-1);
	window.draw(range);
}

void BaseBoid::DrawNear(sf::RenderWindow& window) {
	sf::Vertex neighborLine[2];
	neighborLine[0].color = sf::Color::Green;
	neighborLine[1].color = sf::Color::Red;
	neighborLine[0].position = this->position;
	for (BaseBoid* b : *localBoids) {
		neighborLine[1].position = b->position;
		window.draw(neighborLine, 2, sf::PrimitiveType::Lines);
	}
}

void BaseBoid::DrawTrail(sf::RenderWindow& window) {
	std::list<sf::Vector2f>::iterator it = lastPos.begin();
	std::advance(it, 1);
	sf::Vertex trailLine[2];
	trailLine[0].position = lastPos.front();
	int index = 50;
	for (it; it != lastPos.end(); it++) {
		if ((*it) == sf::Vector2f(0, 0))
			continue;
		//trailLine[0].color = sf::Color(2* index, 4*index, 8*index);
		//trailLine[1].color = sf::Color(64 * index, 32* index, 16 * index);
		//trailLine[0].color = sf::Color(5 * index, 5 * index, 5 * index);
		//trailLine[1].color = sf::Color(5 * index, 5 * index, 5 * index); 
		trailLine[0].color = sf::Color(255, 255, 255, 5 * index);
		trailLine[1].color = sf::Color(255, 255, 255, 5 * index);
		//trailLine[0].color = sf::Color(25* index, 25*index, 25*index);
		//trailLine[1].color = sf::Color(25 * index, 25 * index, 25 * index);
		trailLine[1].position = *it;
		window.draw(trailLine, 2, sf::PrimitiveType::Lines);
		trailLine[0].position = trailLine[1].position;
		index--;
	}
}

void BaseBoid::DrawHighlight(sf::RenderWindow& window){
	sf::CircleShape highlight(shape);
	highlight.setOutlineThickness(3);
	highlight.setOutlineColor(sf::Color(255, 255, 0, 200));
	window.draw(highlight);
}

//Alignment is based on visible boids in the same flock
sf::Vector2f BaseBoid::Alignment() {
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
	align.x /= 8;
	align.y /= 8;
	align = normalize(align);
	return align * alignmentForce;
}

//Cohesion is based on visible boids in the same flock
sf::Vector2f BaseBoid::Cohesion() {
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
	cohesion.x /= 100;
	cohesion.y /= 100;
	cohesion = normalize(cohesion);
	return cohesion * cohesionForce;
}

//Separation is based on visible non-predator boids
sf::Vector2f BaseBoid::Separation() {
	sf::Vector2f separation = { 0,0 };
	int total = 0;
	for (BaseBoid* b : *localBoids) {
		if (!b->isVisible() || b->getFlID() != this->flID)
			continue;
		//float distance = abs(dist(position, b->getPosition()));
		sf::Vector2f distance = position - b->getPosition();
		distance = { abs(distance.x),abs(distance.y) };
		if (distance.x < SEPRANGE && distance.y < SEPRANGE) {
			separation -= position - b->getPosition();
		}
	}
	return separation * separationForce;
}

sf::Vector2f BaseBoid::getPosition() {
	return position;
}

sf::Vector2f BaseBoid::getDirection() {
	return direction;
}

sf::FloatRect BaseBoid::getVisualBoundary() {
	return sf::FloatRect(position.x - visualRadius, position.y - visualRadius,
		visualRadius * 2, visualRadius * 2);
}

sf::Vector2f BaseBoid::checkBounds() {
	sf::Vector2f bound = { 0,0 };
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

