#include "Button.h"

Button::Button(std::string text, sf::Vector2f position, sf::Vector2f size,
	std::function<void()> func)
	:UIElement(position, size) {
	onClick = func;

	bText.setFont(bFont);
	bText.setString(text);
	bText.setFillColor(sf::Color::Black);
	bText.setPosition(
		(position.x + shape.getGlobalBounds().width / 2.5f) - (bText.getLocalBounds().width / 2),
		(position.y + shape.getGlobalBounds().height / 2.5f) - (bText.getLocalBounds().height / 2));
}

void Button::Draw(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(bText);
}

void Button::Update(sf::RenderWindow& window) {
	//Checks click 
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (!isClicked) {
			if (shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
				onClick();
				isClicked = true;
			}
		}
	}
	else
		isClicked = false;
}

void Button::SetText(std::string text) {
	bText.setString(text);
}


void Button::SetFunction(std::function<void()> func) {
	onClick = func;
}

void Button::SetPosition(sf::Vector2f position) {
	shape.setPosition(position);
	bText.setPosition(position + sf::Vector2f(
		shape.getLocalBounds().width * 0.25f,
		shape.getLocalBounds().height * 0.25f));
}

sf::Text Button::GetText() {
	return bText;
}