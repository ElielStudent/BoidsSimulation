#pragma once
#include "SFML/Graphics.hpp"
#include "Functions.h"
#include "constants.h"
#include <list>

enum BoidType { eBaseBoid, eNormalBoid, ePredatorBoid, eUserBoid, eAiBoid };

class BaseBoid {
public:
	BaseBoid(int id, int flID, int x, int y, sf::Color fillColor, sf::Color outlineColor,
		float alignment, float cohesion, float separation);
	void Move();
	void setNeighborBoids(std::list<BaseBoid*>* localBoids);

	void Draw(sf::RenderWindow& window);
	void setColor(sf::Color fillColor = sf::Color::White, sf::Color outlineColor = sf::Color::Black);

	sf::Vector2f getPosition();
	sf::Vector2f getDirection();
	float getVisualRange() { return visualRadius; }
	sf::FloatRect getVisualBoundary();

	void ToggleVisibility() { isvisible = !isvisible; };

	void setAlignment(float alignmentForce) { this->alignmentForce = alignmentForce; };
	void setCohesion(float cohesionForce) { this->cohesionForce = cohesionForce; };
	void setSeparation(float separationForce) { this->separationForce = separationForce; };
	void limitSpeed(float maxspeed = MAXSPEED, float minspeed = MINSPEED);

	bool isVisible() { return isvisible; };
	bool isDead() { return isdead; };
	int getID() { return id; };
	int getFlID() { return flID; };
	BoidType getBoidType() { return boidType; };
	sf::FloatRect getShapeGlobalBounds() { return this->shape.getGlobalBounds(); }

	void setDrawRange(bool state) { drawRange = state; };
	void setDrawNear(bool state) { drawNear = state; };
	void setDrawTrail(bool state) { drawTrail = state; };
	void setDrawHighlight(bool state) { drawHighlight = state; };
protected:
	int id, flID;
	BoidType boidType = BoidType::eBaseBoid;
	std::list<BaseBoid*>* localBoids;

	void DrawVisualRange(sf::RenderWindow& window);
	void DrawNear(sf::RenderWindow& window);
	void DrawTrail(sf::RenderWindow& window);
	void DrawHighlight(sf::RenderWindow& window);
	std::list<sf::Vector2f> lastPos;				//std::list of 10 last pos to draw trail

	virtual void calcDirection() = 0;
	sf::Vector2f checkBounds();
	virtual sf::Vector2f Alignment();
	virtual sf::Vector2f Cohesion();
	virtual sf::Vector2f Separation();

	float getAlignment() { return alignmentForce; }
	float getCohesion() { return cohesionForce; }
	float getSeparation() { return separationForce; }

	float alignmentForce, cohesionForce, separationForce;

	float visualRadius;
	sf::Vector2f position, direction;		//Position/Direction vector
	sf::CircleShape shape;

	bool isvisible = 1, isdead = 0, changeSight = 1;					//Whether other boids can see him, Is eaten, Whether it's visual range increases/decreases
	bool drawRange = 0, drawNear = 0, drawTrail = 0, drawHighlight = 0;
};