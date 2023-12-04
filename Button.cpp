#include "Button.h"
#include "Toolbox.h"

Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick) {
    coordinate = _position;
    // sf::Mouse getPosition;
}
sf::Vector2f Button::getPosition() {
    return coordinate;
}
sf::Sprite* Button::getSprite() {
    return &sprite;
}
void Button::setSprite(sf::Sprite* _sprite) {
    sprite = *_sprite;
}
void Button::onClick() {
    _onClick();
}

