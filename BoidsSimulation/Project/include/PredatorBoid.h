#pragma once
#include "BaseBoid.h"
class PredatorBoid :
	public BaseBoid
{
public:
	PredatorBoid(float alignment, float cohesion, float separation, int id, int flID,
		int x = rand() % GWIDTH, int y = rand() % HEIGHT,
		sf::Color fillColor = sf::Color::White, sf::Color outlineColor = sf::Color::Black);
	void setFollowsRules(bool followsRules) { this->followsRules = followsRules; }
private:
	void calcDirection(sf::Vector2f mousePos = { 0,0 });
	sf::Vector2f ChaseBoid();
	sf::Vector2f Alignment();
	sf::Vector2f Cohesion();
	sf::Vector2f Separation();
	float chasingForce;
	bool followsRules = false;
	bool isChasing = false;
};

