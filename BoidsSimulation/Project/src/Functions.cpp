#include "Functions.h"

 float dist(sf::Vector2f v1, sf::Vector2f v2){
	return sqrt(((v2.x - v1.x) * (v2.x - v1.x)) +
		((v2.y - v1.y) * (v2.y - v1.y)));
}

 float distSqrd(sf::Vector2f v1, sf::Vector2f v2) {
	 return ((v2.x - v1.x) * (v2.x - v1.x)) +
		 ((v2.y - v1.y) * (v2.y - v1.y));
 }

sf::Vector2f normalize(sf::Vector2f v) {
	return v/getMagnitude(v);
}

sf::Vector2f limit(sf::Vector2f v,float limit){
	float mag = abs(getMagnitude(v));
	if (mag > limit) {
		v *= (limit / mag);
	}
	return v;
}

 float getMagnitude(sf::Vector2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

 bool inRadius(sf::Vector2f v1, sf::Vector2f v2, float radius) {
	return (v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y)
		* (v2.y - v1.y) <= (radius * radius);
}


