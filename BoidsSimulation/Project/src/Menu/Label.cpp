#include "Label.h"

Label::Label(std::string text, sf::Vector2f position, sf::Vector2f size,
	std::function<void()> func  )
	:UIElement(position,size) {
	onUpdate = func;

	bText.setFont(bFont);
	bText.setString(text);
	bText.setFillColor(sf::Color::Black);
	bText.setPosition(
		(position.x + shape.getGlobalBounds().width / 2.5f) - (bText.getLocalBounds().width / 2),
		(position.y + shape.getGlobalBounds().height / 2.5f) - (bText.getLocalBounds().height / 2));
}

void Label::Draw(sf::RenderWindow& window) {
	window.draw(shape);
	window.draw(bText);
}

void Label::Update(sf::RenderWindow& window){
	onUpdate();
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

void Label::SetFunction(std::function<void()> func){
	onUpdate = func;
}
