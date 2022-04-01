#pragma once
#include "SFML/Graphics.hpp"
enum class OriginState { TopLeft, TopRight, BottomLeft, BottomRight, Center };

class UIElement {
public:
	UIElement(sf::Vector2f position, sf::Vector2f size);
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void Update(sf::RenderWindow& window) = 0;
	void SetOrigin(OriginState state);
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition();
	void SetSize(sf::Vector2f size);
	sf::Vector2f GetSize();
protected:
	sf::RectangleShape shape;
	sf::Font bFont;
};
