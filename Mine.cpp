#include "Mine.h"
#include "Toolbox.h"
#include <iostream>

Mine::Mine(sf::Vector2f position) : Tile(position) {
    hasMine = true;
    state = HIDDEN;
    coordinate = position;
}
void Mine::setState(State _state) {
    state = _state;
    // Should trigger other behaviors related to the state change (including visualization)
}
Mine::State Mine::getState() {
    return state;
}
void Mine::setNeighbors(std::array<Mine*, 8> _neighbors) {
    neighbors = _neighbors;
}
void Mine::onClickLeft() {
    if (state == HIDDEN) {
        state = EXPLODED;
    }
}
void Mine::onClickRight() {
    if (state == HIDDEN) {
        state = FLAGGED;
    }
    else if (state == FLAGGED){
        state = HIDDEN;
        // add one to mine count
    }
}
void Mine::draw() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (state == HIDDEN) {
        // Create a sprite and set its texture
        sf::Sprite sprite(toolbox.hiddenTile);
        // Set the position of the sprite
        sprite.setPosition(coordinate.x, coordinate.y);
        toolbox.window.draw(sprite);
    }
    else if (state == FLAGGED) {
        // Load the flag texture
        // subtract one from mine count
        sf::Sprite sprite(toolbox.hiddenTile);
        // Set the position of the sprite
        sprite.setPosition(coordinate.x, coordinate.y);
        toolbox.window.draw(sprite);
        sf::Sprite sprite2(toolbox.flag);
        sprite2.setPosition(coordinate.x, coordinate.y);
        // Draw the flag on top of the tile
        toolbox.window.draw(sprite2);
    }
    else if (state == EXPLODED) {
        // subtract one from mine count
        sf::Sprite sprite(toolbox.revealedTile);
        // Set the position of the sprite
        sprite.setPosition(coordinate.x, coordinate.y);
        toolbox.window.draw(sprite);
        sf::Sprite sprite2(toolbox.mine);
        sprite2.setPosition(coordinate.x, coordinate.y);
        // Draw the mine on top of the tile
        toolbox.window.draw(sprite2);
        toolbox.gameState->setPlayStatus(GameState::LOSS);
        toolbox.gameState->getPlayStatus();
    }
}

