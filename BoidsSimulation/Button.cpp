#include "Button.h"

Button::Button(std::string text, sf::Vector2f location, sf::Vector2f size,
	std::function<void()> func) {
	onClick = func;
	shape.setPosition(location);
	shape.setSize(size);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);
	current = false;
	bFont.loadFromFile("Arial.ttf");
	bText.setFont(bFont);
	bText.setString(text);
	bText.setFillColor(sf::Color::Black);
	bText.setPosition(location.x + 3, location.y + 3);
}

void Button::draw(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(bText);
}

void Button::checkClick(sf::Vector2i mousePos) {
	if (mousePos.x >= shape.getPosition().x &&
		mousePos.x <= (shape.getPosition().x + shape.getSize().x) &&
		mousePos.y >= shape.getPosition().y &&
		mousePos.y <= (shape.getPosition().y + shape.getSize().y))
		onClick();
}
void Button::setState(bool state) {
	current = state;
	if (current) {
		shape.setFillColor({ 150,150,150 });
		return;
	}
	shape.setFillColor({ 255,255,255 });
}

bool Button::getState() {
	return current;
}

void Button::setText(std::string text) {
	bText.setString(text);
}

void Button::setPosition(sf::Vector2f location) {
	shape.setPosition(location);
	bText.setPosition(location.x + 3, location.y + 3);
}

sf::Vector2f Button::getLocation() {
	return shape.getPosition();
}

void Button::setSize(sf::Vector2f size) {
	shape.setSize(size);
}

sf::Vector2f Button::getSize() {
	return shape.getSize();
}

void Button::setFunction(std::function<void()> func) {
	onClick = func;
}

sf::Text Button::getText() {
	return bText;
}