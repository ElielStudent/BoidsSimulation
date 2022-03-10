#pragma once
#include "SFML/Graphics.hpp"
#include "Functions.h"
#include "constants.h"
#include <list>

enum class BoidType { eBaseBoid, eNormalBoid, ePredatorBoid, eUserBoid, eAiBoid };

class BaseBoid {
public:
	BaseBoid(int id,int flID, int x = rand() % GWIDTH, int y = rand() % HEIGHT,
		sf::Color fillColor = sf::Color::White,sf::Color outlineColor = sf::Color::Black);
	void Move();
	void setNeighborBoids(std::list<BaseBoid*>* localBoids);

	void Draw(sf::RenderWindow& window);
	void setColor(sf::Color fillColor = sf::Color::White, sf::Color outlineColor = sf::Color::Black);

	virtual void calcDirection() = 0;
	sf::Vector2f getPosition();
	sf::Vector2f getDirection();

	float getVisualRange() { return visualRadius; }
	sf::FloatRect getVisualBoundary();

	int id;
	int flID;
	BoidType boidType = BoidType::eBaseBoid;

	void ToggleVisibility();
	bool isVisible = 1;			//Whether other boids can see him
	bool isDead = 0;			//Is eaten
	bool changeSight = 1;		//Whether it's visual range increases/decreases

	bool drawRange = 1;
	bool drawNeighbors = 1;
	bool drawTrail = 1;
	bool drawDirection = 1;

	virtual void setAlignment(float alignmentForce) = 0;
	virtual void setCohesion(float cohesionForce) = 0;
	virtual void setSeparation(float separationForce) = 0;
protected:
	std::list<BaseBoid*>* localBoids;

	void DrawVisualRange(sf::RenderWindow& window);
	void DrawNeighbors(sf::RenderWindow& window);
	void DrawTrail(sf::RenderWindow& window);
	std::list<sf::Vector2f> lastPos;				//std::list of 10 last pos to draw trail
	void DrawDirection(sf::RenderWindow& window);

	sf::Vector2f checkBounds();
	float visualRadius;
	sf::Vector2f position;
	sf::Vector2f direction;			//Direction vector
	sf::CircleShape shape;
};