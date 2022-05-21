#include "BToggle.h"

BToggle::BToggle(std::string text, sf::Vector2f position, sf::Vector2f size,
	std::function<void()> clickFunc, std::function<void()>unClickFunc)
	:UIElement(position, size) {
	onClick = clickFunc;
	onUnClick = unClickFunc;

	bText.setFont(bFont);
	bText.setString(text);
	bText.setFillColor(sf::Color::Black);
	bText.setPosition(
		(position.x + shape.getGlobalBounds().width / 2.5f) - (bText.getLocalBounds().width / 2),
		(position.y + shape.getGlobalBounds().height / 2.5f) - (bText.getLocalBounds().height / 2));

	currentState = false;
}

void BToggle::Draw(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(bText);
}

void BToggle::Update(sf::RenderWindow& window) {
	//Checks click 
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (!isClicked) {
			if (shape.getGlobalBounds().contains(
				window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
				SetState(!currentState);
				if(currentState)	//If it has been clicked now
					onClick();
				if (!currentState)	//If it was un-clicked
					onUnClick();
			}
			isClicked = true;
		}
	}
	else 
		isClicked = false;
	
}

void BToggle::SetState(bool state) {
	currentState = state;
	if (currentState) {
		shape.setFillColor({ 150,150,150 });
		return;
	}
	shape.setFillColor({ 255,255,255 });
}

bool BToggle::GetState() {
	return currentState;
}

void BToggle::SetText(std::string text) {
	bText.setString(text);
}

void BToggle::SetFunction(std::function<void()> func) {
	onClick = func;
}

void BToggle::SetPosition(sf::Vector2f position) {
	shape.setPosition(position);
	bText.setPosition(position + sf::Vector2f(
		shape.getLocalBounds().width * 0.25f,
		shape.getLocalBounds().height * 0.25f));
}


sf::Text BToggle::GetText() {
	return bText;
}