#include "BaseBoid.h"

BaseBoid::BaseBoid( int id, int x, int y) {
	visualRange = BOIDSIGHT;

	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color::Black);
	shape.setRadius(BOIDRADIUS);
	shape.setPointCount(3);
	shape.setOrigin(BOIDRADIUS/2, BOIDRADIUS/2);
	shape.setScale(1, 1.5);


	position = Vector2f(x, y);
	shape.setPosition(position);
	shape.setRotation(rand() % 360);

	direction.x = float(cos((3.1415 / 180) * shape.getRotation()));
	direction.y = float(sin((3.1415 / 180) * shape.getRotation()));

	this->id = id;

	localBoids = nullptr;
}

void BaseBoid::Move() {
	calcDirection();

	this->shape.setRotation(atan2f(direction.x, -direction.y) * (180 / 3.1415));

	this->position += direction;
	this->shape.setPosition(this->position);
}

void BaseBoid::setNeighborBoids(std::list<BaseBoid*>* localBoids){
	delete this->localBoids;
	this->localBoids = localBoids;
}

//Option to draw range, nearby boids
void BaseBoid::Draw(sf::RenderWindow& window) {
	
	window.draw(shape);
}

void BaseBoid::DrawVisualRange(sf::RenderWindow& window){
	CircleShape range;
	range.setRadius(this->visualRange / 2);
	range.setPosition({ this->position.x- this->visualRange / 2 ,
		this->position.y - this->visualRange / 2 });
	range.setFillColor(Color::Transparent);
	range.setOutlineColor(Color::White);
	range.setOutlineThickness(-1);
	window.draw(range);
}

void BaseBoid::DrawNeighbors(sf::RenderWindow& window){
	Vertex neighborLine[2];
	neighborLine[0].color = Color::Green;
	neighborLine[1].color = Color::Red;
	neighborLine[0].position = this->position;
	for (BaseBoid* b : *localBoids) {
		neighborLine[1].position = b->position;
		window.draw(neighborLine, 2, PrimitiveType::Lines);
	}
}

Vector2f BaseBoid::getPosition(){
	return position;
}

Vector2f BaseBoid::getDirection(){
	return direction;
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

