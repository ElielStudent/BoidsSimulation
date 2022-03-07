#include "BaseBoid.h"

BaseBoid::BaseBoid(int id, int x, int y) {
	visualRadius = BOIDSIGHT;

	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color::Black);
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

	this->id = id;

	localBoids = nullptr;

	for (int i = 0; i < 50; i++)
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
	if (this->drawNeighbors)
		DrawNeighbors(window);
	if (this->drawTrail)
		DrawTrail(window);
	window.draw(shape);
}

void BaseBoid::DrawVisualRange(sf::RenderWindow& window) {
	sf::CircleShape range;
	range.setRadius(this->visualRadius);
	range.setPosition({ this->position.x - this->visualRadius  ,
		this->position.y - this->visualRadius  });
	range.setFillColor(sf::Color::Transparent);
	range.setOutlineColor(sf::Color::White);
	range.setOutlineThickness(-1);
	window.draw(range);
}

void BaseBoid::DrawNeighbors(sf::RenderWindow& window) {
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
		//trailLine[0].color = Color(2* index, 4*index, 8*index);
		//trailLine[1].color = Color(64 * index, 32* index, 16 * index);
		trailLine[0].color = sf::Color(5 * index, 5 * index, 5 * index);
		trailLine[1].color = sf::Color(5 * index, 5 * index, 5 * index);
		//trailLine[0].color = Color(25* index, 25*index, 25*index);
		//trailLine[1].color = Color(25 * index, 25 * index, 25 * index);
		trailLine[1].position = *it;
		window.draw(trailLine, 2, sf::PrimitiveType::Lines);
		trailLine[0].position = trailLine[1].position;
		index--;
	}
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

