#include "Label.h"

Label::Label(std::string text, sf::Vector2f position, sf::Vector2f size,
	sf::Color fillColor, sf::Color outlineColor )
	:UIElement(position,size,fillColor, outlineColor) {
	shape.setFillColor(sf::Color::White);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);

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
	bText.setPosition(position + sf::Vector2f(
		shape.getLocalBounds().width * 0.25f,
		shape.getLocalBounds().height * 0.25f));
}

sf::Text Label::GetText() {
	return bText;
}