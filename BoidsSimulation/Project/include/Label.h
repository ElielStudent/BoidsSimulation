#pragma once
#include "UIElement.h"
#include <SFML/Graphics.hpp>
class Label :UIElement {
public:
	Label(std::string = "NULL", sf::Vector2f position = { 0,0 }, sf::Vector2f size = { 100, 50 },
		sf::Color fill = sf::Color::White, sf::Color outline = sf::Color::Black);
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void SetText(std::string);
	sf::Text GetText();
	void SetPosition(sf::Vector2f position);
private:
	sf::Text bText;
};

