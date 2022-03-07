#pragma once
#include <SFML/Graphics.hpp>

float dist(sf::Vector2f v1, sf::Vector2f v2);
float distSqrd(sf::Vector2f v1, sf::Vector2f v2);
sf::Vector2f normalize(sf::Vector2f v);
sf::Vector2f limit(sf::Vector2f v, float limit);
float getMagnitude(sf::Vector2f v);	//length of the vector
bool inRadius(sf::Vector2f v1, sf::Vector2f v2, float radius);
