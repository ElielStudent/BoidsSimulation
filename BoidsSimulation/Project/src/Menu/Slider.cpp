#include "Slider.h"

Slider::Slider(std::string text, float lower, float higher,float starter, sf::Vector2f position,
	sf::Vector2f size, std::function<void(float)> func) :UIElement(position, size) {
	sliderFunc = func;
	sliderText.setFont(bFont);
	valueText.setFont(bFont);
	isClicked = false;

	minval = lower;
	maxval = higher;
	sliderText.setString(text);
	valueText.setString(text + ": " + std::to_string(int(starter*100)/100));
	valueText.setFillColor(sf::Color::Black);

	shape.setFillColor(sf::Color::White);
	valueShowShape.setFillColor(sf::Color(120, 120, 120));

	shape.setPosition(position);
	shape.setSize(size);
	valueShowShape.setPosition(position);
	valueShowShape.setSize({ 0,size.y });

	sliderText.setPosition(
		(position.x + shape.getGlobalBounds().width / 2.5f) - (sliderText.getLocalBounds().width / 2),
		(position.y + shape.getGlobalBounds().height / 2.5f) - (sliderText.getLocalBounds().height / 2) + 10);

	valueText.setPosition(
		(position.x + shape.getGlobalBounds().width / 2.5f) - (valueText.getLocalBounds().width / 2),
		(position.y + shape.getGlobalBounds().height / 2.5f) - (valueText.getLocalBounds().height / 2));
	
	SetValue(starter);
}

void Slider::Draw(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(valueShowShape);
	window.draw(valueText);
}

void Slider::Update(sf::RenderWindow& window) { 
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if (shape.getGlobalBounds().contains(mousePos)) {
			isClicked = true;
		}
		if (isClicked) {
			value = std::min(maxval,std::max(0.f,CalculateValue(mousePos, window)));
			valueText.setString(sliderText.getString() + ": " + std::to_string(value).substr(0,5));
			float ratio = value / (minval + maxval);
			valueShowShape.setSize({ shape.getSize().x * ratio,shape.getSize().y });
			sliderFunc(value);
		}
	}
	else isClicked = false;
}

void Slider::SetValue(float val){
	value = val;
	value = std::min(maxval, std::max(minval, value));
	valueText.setString(sliderText.getString() + ": " + std::to_string(value).substr(0, 5));
	float ratio = value / (minval + maxval);
	valueShowShape.setSize({ shape.getSize().x * ratio,shape.getSize().y });
	sliderFunc(value);
}

float Slider::CalculateValue(sf::Vector2f mousePos, sf::RenderWindow& window){
	float ratio = mousePos.x / (shape.getGlobalBounds().left + shape.getGlobalBounds().width);
	return (minval+maxval)*ratio;
}