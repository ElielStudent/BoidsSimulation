#include "Button.h"

Button::Button(std::string text, sf::Vector2f position, sf::Vector2f size, std::function<void()> func)
	:UIElement(sf::FloatRect(position.x, position.y, size.x, size.y)) {
	onClick = func;

	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);

	bFont.loadFromFile("Arial.ttf");
	bText.setFont(bFont);
	bText.setString(text);
	bText.setFillColor(sf::Color::Black);
	bText.setPosition(position.x + 3, position.y + 3);
}

void Button::Draw(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(bText);
}

void Button::Update(sf::RenderWindow& window) {
	//Checks click 
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (!isClicked) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			if (getBoundary()->contains(mousePos.x, mousePos.y)) {
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

void Button::SetPosition(sf::Vector2f position) {
	shape.setPosition(position);
	bText.setPosition(position.x + 3, position.y + 3);

}

sf::Vector2f Button::GetPosition() {
	return shape.getPosition();
}

void Button::SetSize(sf::Vector2f size) {
	shape.setSize(size);
}

sf::Vector2f Button::GetSize() {
	return shape.getSize();
}

void Button::SetOrigin(OriginState state) {
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

void Button::SetFunction(std::function<void()> func) {
	onClick = func;
}

sf::Text Button::GetText() {
	return bText;
}