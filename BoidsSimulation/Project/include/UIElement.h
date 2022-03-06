#pragma once
#include "SFML/Graphics.hpp"
enum class OriginState { TopLeft,TopRight,BottomLeft,BottomRight,Center };

class UIElement{
public:
	UIElement(sf::FloatRect boundingRect);
	virtual void Draw(sf::RenderWindow &window) = 0;
	virtual void Update(sf::RenderWindow& window) = 0;
	virtual sf::FloatRect* getBoundary();
protected:
	sf::FloatRect boundary;
};

