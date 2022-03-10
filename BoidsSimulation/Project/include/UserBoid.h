#pragma once
#include "BaseBoid.h"
class UserBoid :
	public BaseBoid
{
public:
	UserBoid(int id, int flID, int x = rand() % GWIDTH, int y = rand() % HEIGHT);
	void calcDirection();
	void setAlignment(float alignmentForce);
	void setCohesion(float cohesionForce);
	void setSeparation(float separationForce);
};

