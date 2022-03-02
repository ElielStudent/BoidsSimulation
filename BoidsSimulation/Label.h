#pragma once
#include "UIElement.h"
#include <SFML/Graphics.hpp>
class Label:UIElement{
public:
	Label(std::string = "NULL", sf::Vector2f position = { 0,0 }
	, sf::Vector2f size = { 100, 50 });
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void SetText(std::string);
	sf::Text GetText();
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition();
	void SetSize(sf::Vector2f size);
	sf::Vector2f GetSize();
	void SetOrigin(OriginState state);
private:
	sf::RectangleShape shape;
	sf::Font bFont;
	sf::Text bText;
};

