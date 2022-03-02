#pragma once
#include "SFML/Graphics.hpp"
#include "Functions.h"
#include "constants.h"
#include <list>

using namespace sf;
using namespace std;

class BaseBoid {
public:
	BaseBoid(float alignment, float cohesion, float separation,
		int id, int x = rand() % GWIDTH, int y = rand() % HEIGHT);
	virtual void Move(std::list<BaseBoid*>& boids);
	virtual void Draw(sf::RenderWindow& window);

	virtual void calcDirection(std::list<BaseBoid*>& boids) = 0;
	Vector2f getPosition();
	FloatRect getVisualRange();
	int id;

	float alignmentForce;
	float cohesionForce;
	float separationForce;
	float visualRange;
private:
	bool isDead = 0;			//Is eaten
	bool isVisible = 1;			//Whether other boids can see him
	bool changeSight = 1;
	Vector2f position;
	Vector2f direction;			//Movement not normalized
	sf::CircleShape shape;

	Vector2f checkBounds();
	Vector2f Alignment(std::list<BaseBoid*>& boids);
	Vector2f Cohesion(std::list<BaseBoid*>& boids);
	Vector2f Separation(std::list<BaseBoid*>& boids);
};