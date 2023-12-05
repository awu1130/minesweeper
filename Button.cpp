#include "Button.h"

Button::Button(sf::Vector2f _position, std::function<void(void)> _onClick) {
    coordinate = _position;
    this->_onClick = _onClick;
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
// fix onClick
void Button::onClick() {
    _onClick();
}

