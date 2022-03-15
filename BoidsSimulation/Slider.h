#pragma once
#include "SFML/Graphics.hpp"
#include "UIElement.h"
#include <functional>

class Slider :
    public UIElement
{
public:
	Slider(float lower,float higher,float interval,sf::Vector2f position = { 0,0 }, sf::Vector2f size = { 100, 50 },
		std::function<void()> func = []() {return; }, sf::Color fill = sf::Color::White, sf::Color outline = sf::Color::Black);
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void SetText(std::string);
	sf::Text GetText();
	void SetFunction(std::function<void()> func);
	void SetPosition(sf::Vector2f position);
private:
	float value;
	sf::Text valueText;
	sf::RectangleShape lineShape;
	sf::CircleShape sliderShape;
	bool isClicked = false;
	std::function<void()> onClick;
};