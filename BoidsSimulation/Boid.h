#pragma once
#include "SFML/Graphics.hpp"
#include "Functions.h"
#include "constants.h"
#include <list>

using namespace sf;
using namespace std;

class Boid {
public:
	Boid(float alignment, float cohesion, float separation,
		int id, int x = rand() % WIDTH, int y = rand() % HEIGHT);
	void Move(std::list<Boid*>& boids);
	void Draw(sf::RenderWindow& window);
	int id;

	float alignmentForce;
	float cohesionForce;
	float separationForce;
private:
	bool isDead = 0;			//Is eaten
	bool isVisible = 1;			//Whether other boids can see him
	Vector2f position;
	Vector2f velocity;			//Movement not normalized
	sf::CircleShape shape;

	Vector2f checkBounds();
	Vector2f Alignment(std::list<Boid*>& boids);
	Vector2f Cohesion(std::list<Boid*>& boids);
	Vector2f Separation(std::list<Boid*>& boids);
};