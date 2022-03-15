#pragma once
#include "BaseBoid.h"
class UserBoid :
	public BaseBoid
{
public:
	UserBoid(int id, int flID, int x = rand() % GWIDTH, int y = rand() % HEIGHT,
		sf::Color fillColor = sf::Color::White, sf::Color outlineColor = sf::Color::Black);
private:
	void calcDirection();
};

