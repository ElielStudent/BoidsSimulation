#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

 float dist(Vector2f v1, Vector2f v2);
 float distSqrd(Vector2f v1, Vector2f v2);
Vector2f normalize(Vector2f v);
Vector2f limit(Vector2f v,float limit);
 float getMagnitude(Vector2f v);	//length of the vector
bool inRadius(Vector2f v1, Vector2f v2, float radius);
