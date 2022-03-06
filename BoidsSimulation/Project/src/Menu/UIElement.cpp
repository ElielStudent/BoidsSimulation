#include "UIElement.h"

UIElement::UIElement(sf::FloatRect boundingRect) :boundary(boundingRect) {}

sf::FloatRect* UIElement::getBoundary() {
	return &boundary;
}
