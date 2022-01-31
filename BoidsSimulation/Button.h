#pragma once
#include "SFML/Graphics.hpp"

class Button {
public:
    Button(std::string = "NULL", sf::Vector2f location = { 0,0 });
    void draw(sf::RenderWindow& window);
    void checkClick(sf::Vector2f);
    void setState(bool);
    bool getState();
    void setText(std::string);
    sf::Text getText();
    void setLocation(sf::Vector2f location);
    sf::Vector2f getLocation();
    void setSize(sf::Vector2f size);
    sf::Vector2f getSize();
private:
    sf::RectangleShape shape;
    sf::Font bFont;
    sf::Text bText;
    bool current;
};