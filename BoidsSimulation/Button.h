#pragma once
#include "SFML/Graphics.hpp"
#include <functional>

class Button {
public:
    Button(std::string = "NULL", sf::Vector2f location = { 0,0 }
        ,sf::Vector2f size = { 100, 50 }, std::function<void()> func = []() {return; });
    void draw(sf::RenderWindow& window);
    void checkClick(sf::Vector2i);
    void setState(bool);
    bool getState();
    void setText(std::string);
    sf::Text getText();
    void setPosition(sf::Vector2f location);
    sf::Vector2f getLocation();
    void setSize(sf::Vector2f size);
    sf::Vector2f getSize();
    void setFunction(std::function<void()> func);
    std::function<void()> onClick;
private:
    sf::RectangleShape shape;
    sf::Font bFont;
    sf::Text bText;
    bool current;
};