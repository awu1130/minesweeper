#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    Button(sf::Vector2f _position, std::function<void(void)> _onClick);
    sf::Vector2f getPosition();
    sf::Sprite* getSprite();
    void setSprite(sf::Sprite* _sprite);
    void onClick();
private:
    sf::Vector2f coordinate;
    sf::Sprite sprite;
    std::function<void(void)> _onClick;
};

