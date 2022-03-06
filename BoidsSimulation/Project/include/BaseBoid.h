#pragma once
#include "SFML/Graphics.hpp"
#include "Functions.h"
#include "constants.h"
#include <list>

using namespace sf;
using namespace std;

enum class BoidType { eBaseBoid, eNormalBoid, ePredatorBoid, eUserBoid, eAiBoid };

class BaseBoid {
public:
	BaseBoid( int id,
		int x = rand() % GWIDTH, int y = rand() % HEIGHT);
	void Move();
	void setNeighborBoids(std::list<BaseBoid*>* localBoids);
	void Draw(sf::RenderWindow& window);
	void DrawVisualRange(sf::RenderWindow& window);
	void DrawNeighbors(sf::RenderWindow& window);
	void DrawTrail(sf::RenderWindow& window);

	virtual void calcDirection() = 0;
	Vector2f getPosition();
	Vector2f getDirection();

	float getVisualRange() { return visualRange; }
	FloatRect getVisualBoundary();

	int id;
	BoidType boidType = BoidType::eBaseBoid;
	bool isVisible = 1;			//Whether other boids can see him
	bool isDead = 0;			//Is eaten
	bool changeSight = 1;		//Whether it's visual range increases/decreases
	bool drawRange = 1;
	bool drawNeighbors = 1;
	bool drawTrail = 1;

	virtual void setAlignment(float alignmentForce) = 0;
	virtual void setCohesion(float cohesionForce) = 0;
	virtual void setSeparation(float separationForce) = 0;
protected:
	std::list<BaseBoid*>* localBoids;
	list<Vector2f> lastPos;				//list of 10 last pos to draw trail
	Vector2f checkBounds();
	float visualRange;
	Vector2f position;
	Vector2f direction;			//Movement not normalized
	sf::CircleShape shape;
};