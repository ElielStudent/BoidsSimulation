#pragma once
#include "SFML/Graphics.hpp"
#include "UIElement.h"
#include <functional>

class Button :public UIElement {
public:
	Button(std::string = "NULL", sf::Vector2f position = { 0,0 }
	, sf::Vector2f size = { 100, 50 }, std::function<void()> func = []() {return; });
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void SetText(std::string);
	sf::Text GetText();
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition();
	void SetSize(sf::Vector2f size);
	sf::Vector2f GetSize();
	void SetOrigin(OriginState state);
	void SetFunction(std::function<void()> func);
private:
	bool isClicked = false;
	std::function<void()> onClick;
	sf::RectangleShape shape;
	sf::Font bFont;
	sf::Text bText;
};