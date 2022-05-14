#include "UserBoid.h"

UserBoid::UserBoid(int id, int flID, int x, int y, sf::Color fillColor, sf::Color outlineColor)
	:BaseBoid(id, flID, x, y, fillColor, outlineColor,ALIGNMENT,COHESION,SEPARATION) {
	boidType = BoidType::eUserBoid;
	direction = { 0,-5 };
}

void UserBoid::calcDirection() {
	float USERTURN = 0.1f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		direction = { cos(USERTURN) * direction.x - sin(USERTURN) * direction.y,
		cos(USERTURN) * direction.y + sin(USERTURN) * direction.x };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		direction = { cos(-USERTURN) * direction.x - sin(-USERTURN) * direction.y,
		cos(-USERTURN) * direction.y + sin(-USERTURN) * direction.x };
	limitSpeed();
	direction += checkBounds();
}

