#include <array>
#include "Tile.h"
#include "Toolbox.h"
#include <iostream>

Tile::Tile(sf::Vector2f position) {
    coordinate = position;
    state = HIDDEN;
}
sf::Vector2f Tile::getLocation() {
    return coordinate;
}
Tile::State Tile::getState() {
    return state;
}
/*
std::array<Tile*, 8>& Tile::getNeighbors() {
    return neighbors;
}*/
void Tile::setState(State _state) {
    state = _state;
    // Should trigger other behaviors related to the state change (including visualization)
}
/*
void Tile::setNeighbors(std::array<Tile*, 8> _neighbors) {
    neighbors = _neighbors;
}
*/
void Tile::onClickLeft() {
    if (state == HIDDEN) {
        state = REVEALED;
    }
    //else if (state == EXPLODED) {

    //}
}
void Tile::onClickRight() {
    if (state == HIDDEN) {
        state = FLAGGED;
        // subtract one from mine count
    }
    else if (state == FLAGGED){
        state = HIDDEN;
        // add one to mine count
    }
}

void Tile::draw() {
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
    else if (state == REVEALED) {
        sf::Sprite sprite2(toolbox.revealedTile);
        sprite2.setPosition(coordinate.x, coordinate.y);
        // Draw the flag on top of the tile
        toolbox.window.draw(sprite2);
    }
}

