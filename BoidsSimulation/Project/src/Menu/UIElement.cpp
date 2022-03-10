#include "UIElement.h"

UIElement::UIElement(sf::Vector2f position, sf::Vector2f size ,sf::Color fillColor,sf::Color outlineColor) {
	bFont.loadFromFile("Arial.ttf");
	shape.setPosition(position);
	shape.setSize(size);

	shape.setFillColor(fillColor);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(outlineColor);
}

void UIElement::SetOrigin(OriginState state) {
	sf::FloatRect boundary = shape.getGlobalBounds();
	switch (state) {
	case OriginState::TopLeft:
		shape.setOrigin(boundary.left, boundary.top);
		break;
	case OriginState::TopRight:
		shape.setOrigin(boundary.left + boundary.width, boundary.top);
		break;
	case OriginState::BottomLeft:
		shape.setOrigin(boundary.left, boundary.top + boundary.height);
		break;
	case OriginState::BottomRight:
		shape.setOrigin(boundary.left + boundary.width, boundary.top + boundary.height);
		break;
	case OriginState::Center:
		shape.setOrigin(boundary.left + (boundary.width / 2), boundary.top + (boundary.height / 2));
		break;
	default:
		break;
	}
}

void UIElement::SetPosition(sf::Vector2f position) {
	shape.setPosition(position);
}

sf::Vector2f UIElement::GetPosition() {
	return shape.getPosition();
}

void UIElement::SetSize(sf::Vector2f size) {
	shape.setSize(size);
}

sf::Vector2f UIElement::GetSize() {
	return shape.getSize();
}