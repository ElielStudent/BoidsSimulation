#pragma once
#include "BaseBoid.h"
class PredatorBoid :
	public BaseBoid
{
public:
	PredatorBoid(float alignment, float cohesion, float separation, int id, int flID,
		int x = rand() % GWIDTH, int y = rand() % HEIGHT,
		sf::Color fillColor = sf::Color::White, sf::Color outlineColor = sf::Color::Black);
private:
	void calcDirection();
	sf::Vector2f ChaseBoid();

	float chasingForce = 10;
};

