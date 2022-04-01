#pragma once
#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <functional>

class Label :public UIElement {
public:
	Label(std::string = "NULL", sf::Vector2f position = { 0,0 }, sf::Vector2f size = { 100, 50 },
		std::function<void()> func = []() {return; });
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void SetText(std::string);
	sf::Text GetText();
	void SetFunction(std::function<void()> func);
	void SetPosition(sf::Vector2f position);
private:
	std::function<void()> onUpdate;
	sf::Text bText;
};

