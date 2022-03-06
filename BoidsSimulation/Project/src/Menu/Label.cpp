#include "Label.h"

Label::Label(std::string text, sf::Vector2f position, sf::Vector2f size)
	:UIElement(sf::FloatRect(position.x, position.y, size.x, size.y)) {
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

void Label::Draw(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(bText);
}

void Label::Update(sf::RenderWindow& window)
{
}

void Label::SetText(std::string text) {
	bText.setString(text);
}

void Label::SetPosition(sf::Vector2f position) {
	shape.setPosition(position);
	bText.setPosition(position.x + 3, position.y + 3);

}

sf::Vector2f Label::GetPosition() {
	return shape.getPosition();
}

void Label::SetSize(sf::Vector2f size) {
	shape.setSize(size);
}

sf::Vector2f Label::GetSize() {
	return shape.getSize();
}

void Label::SetOrigin(OriginState state) {
	sf::FloatRect* boundary = getBoundary();
	switch (state) {
	case OriginState::TopLeft:
		shape.setOrigin(boundary->left, boundary->top);
		break;
	case OriginState::TopRight:
		shape.setOrigin(boundary->left + boundary->width, boundary->top);
		break;
	case OriginState::BottomLeft:
		shape.setOrigin(boundary->left, boundary->top + boundary->height);
		break;
	case OriginState::BottomRight:
		shape.setOrigin(boundary->left + boundary->width, boundary->top + boundary->height);
		break;
	case OriginState::Center:
		shape.setOrigin(boundary->left + (boundary->width / 2), boundary->top + (boundary->height / 2));
		break;
	default:
		break;
	}
}

sf::Text Label::GetText() {
	return bText;
}