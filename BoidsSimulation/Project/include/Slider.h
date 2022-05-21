#pragma once
#include "SFML/Graphics.hpp"
#include "UIElement.h"
#include <algorithm>
#include <functional>

class Slider :
	public UIElement
{
public:
	Slider(std::string text, float lower, float higher,float starter,
		sf::Vector2f position = { 0,0 }, sf::Vector2f size = { 100, 50 },
		std::function<void(float)> func = [](float f) {return; });
	void Draw(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void SetSliderText(std::string text) { sliderText.setString(text); };
	void SetFunc(std::function<void(float)> func) { sliderFunc = func; };
	void SetValueText(std::string text) { valueText.setString(text); };
	sf::Text GetSliderText() { return sliderText; };
	void SetValue(float val);
	float GetValue() { return value; };
private:
	float CalculateValue(sf::Vector2f mousePos,sf::RenderWindow& window);
	float value;
	float minval,maxval;
	sf::Text sliderText;
	sf::Text valueText;
	sf::RectangleShape valueShowShape;
	std::function<void(float)> sliderFunc;
	bool isClicked;
};