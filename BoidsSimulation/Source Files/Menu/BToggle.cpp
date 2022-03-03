#include "BToggle.h"

BToggle::BToggle(std::string text, sf::Vector2f position, sf::Vector2f size, std::function<void()> func)
	:UIElement(sf::FloatRect(position.x, position.y, size.x, size.y)) {
	onClick = func;
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);
	currentState = false;
	bFont.loadFromFile("Arial.ttf");
	bText.setFont(bFont);
	bText.setString(text);
	bText.setFillColor(sf::Color::Black);
	bText.setPosition(position.x + 3, position.y + 3);
}

void BToggle::Draw(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(bText);
}

void BToggle::Update(sf::RenderWindow& window) {
	//Checks click 
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (!isClicked) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			if (getBoundary()->contains(mousePos.x, mousePos.y)) {
				SetState(!currentState);
				onClick();
				isClicked = true;
			}
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

void BToggle::SetPosition(sf::Vector2f position) {
	shape.setPosition(position);
	bText.setPosition(position.x + 3, position.y + 3);

}

sf::Vector2f BToggle::GetPosition() {
	return shape.getPosition();
}

void BToggle::SetSize(sf::Vector2f size) {
	shape.setSize(size);
}

sf::Vector2f BToggle::GetSize() {
	return shape.getSize();
}

void BToggle::SetOrigin(OriginState state) {
	sf::FloatRect* boundary = getBoundary();
	switch (state) {
	case TopLeft:
		shape.setOrigin(boundary->left, boundary->top);
		break;
	case TopRight:
		shape.setOrigin(boundary->left + boundary->width, boundary->top);
		break;
	case BottomLeft:
		shape.setOrigin(boundary->left, boundary->top + boundary->height);
		break;
	case BottomRight:
		shape.setOrigin(boundary->left + boundary->width, boundary->top + boundary->height);
		break;
	case Center:
		shape.setOrigin(boundary->left + (boundary->width / 2), boundary->top + (boundary->height / 2));
		break;
	default:
		break;
	}
}

void BToggle::SetFunction(std::function<void()> func) {
	onClick = func;
}

sf::Text BToggle::GetText() {
	return bText;
}