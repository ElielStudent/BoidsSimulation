#include "Functions.h"

float dist(Vector2f v1, Vector2f v2){
	return sqrt(((v2.x - v1.x) * (v2.x - v1.x)) +
		((v2.y - v1.y) * (v2.y - v1.y)));
}

Vector2f normalize(Vector2f v) {
	return v/getMagnitude(v);
}

Vector2f limit(Vector2f v,float limit){
	float mag = abs(getMagnitude(v));
	if (mag > limit) {
		v *= (limit / mag);
	}
	return v;
}

float getMagnitude(Vector2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

bool inRadius(Vector2f v1, Vector2f v2, float radius) {
	return (v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y)
		* (v2.y - v1.y) <= (radius * radius);
}


