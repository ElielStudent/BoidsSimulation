#include "UserBoid.h"

UserBoid::UserBoid(int id,int flID, int x, int y) :BaseBoid(id,flID, x, y) {
	boidType = BoidType::eUserBoid;
}

void UserBoid::calcDirection() {
	float USERTURN = 0.1f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		direction = { cos(USERTURN) * direction.x - sin(USERTURN) * direction.y,
		cos(USERTURN) * direction.y + sin(USERTURN) * direction.x };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		direction = { cos(-USERTURN) * direction.x - sin(-USERTURN) * direction.y,
		cos(-USERTURN) * direction.y + sin(-USERTURN) * direction.x };
	direction = normalize(direction);
	direction.x *= MAXSPEED;
	direction.y *= MAXSPEED;
	direction += checkBounds();
}

void UserBoid::setAlignment(float alignmentForce) {}

void UserBoid::setCohesion(float cohesionForce) {}

void UserBoid::setSeparation(float separationForce) {}
