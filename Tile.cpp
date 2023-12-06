#include <array>
#include "Tile.h"
#include "Toolbox.h"

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
std::array<Tile*, 8>& Tile::getNeighbors() {
    return neighbors;
}
void Tile::setState(State _state) {
    state = _state;
    // Should trigger other behaviors related to the state change (including visualization)
}
void Tile::setNeighbors(std::array<Tile*, 8> _neighbors) {
    neighbors = _neighbors;
}
void Tile::onClickLeft() {
    if (state == HIDDEN) {
        revealNeighbors();
    }
}
void Tile::onClickRight() {
    if (state == HIDDEN) {
        state = FLAGGED;
    }
    else if (state == FLAGGED){
        state = HIDDEN;
    }
}
void Tile::draw() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (state == HIDDEN) {
        sf::Sprite sprite(toolbox.hiddenTile);
        sprite.setPosition(coordinate.x, coordinate.y);
        toolbox.window.draw(sprite);
    }
    else if (state == FLAGGED) {
        // hidden tile
        sf::Sprite sprite(toolbox.hiddenTile);
        sprite.setPosition(coordinate.x, coordinate.y);
        toolbox.window.draw(sprite);
        // flag on top
        sf::Sprite sprite2(toolbox.flag);
        sprite2.setPosition(coordinate.x, coordinate.y);
        toolbox.window.draw(sprite2);
    }
    else if (state == REVEALED) {
        // revealed tile
        sf::Sprite sprite(toolbox.revealedTile);
        sprite.setPosition(coordinate.x, coordinate.y);
        toolbox.window.draw(sprite);
        if (numNeighborMines == 1) {
            sf::Sprite sprite2(toolbox.number1);
            sprite2.setPosition(coordinate.x, coordinate.y);
            // Draw the number on top of the tile
            toolbox.window.draw(sprite2);
        } else if (numNeighborMines == 2) {
            sf::Sprite sprite2(toolbox.number2);
            sprite2.setPosition(coordinate.x, coordinate.y);
            toolbox.window.draw(sprite2);
        } else if (numNeighborMines == 3) {
            sf::Sprite sprite2(toolbox.number3);
            sprite2.setPosition(coordinate.x, coordinate.y);
            toolbox.window.draw(sprite2);
        } else if (numNeighborMines == 4) {
            sf::Sprite sprite2(toolbox.number4);
            sprite2.setPosition(coordinate.x, coordinate.y);
            toolbox.window.draw(sprite2);
        } else if (numNeighborMines == 5) {
            sf::Sprite sprite2(toolbox.number5);
            sprite2.setPosition(coordinate.x, coordinate.y);
            toolbox.window.draw(sprite2);
        } else if (numNeighborMines == 6) {
            sf::Sprite sprite2(toolbox.number6);
            sprite2.setPosition(coordinate.x, coordinate.y);
            toolbox.window.draw(sprite2);
        } else if (numNeighborMines == 7) {
            sf::Sprite sprite2(toolbox.number7);
            sprite2.setPosition(coordinate.x, coordinate.y);
            toolbox.window.draw(sprite2);
        } else if (numNeighborMines == 8) {
            sf::Sprite sprite2(toolbox.number8);
            sprite2.setPosition(coordinate.x, coordinate.y);
            toolbox.window.draw(sprite2);
        }
    }
}
void Tile::revealNeighbors() {
    // check if hidden
        // reveal
        // if not bomb
            // for in neighbors
                // recursive
    if (state == HIDDEN) {
        state = REVEALED;
        numNeighborMines = 0;
        for (int i = 0; i < 8; i++) {
            if (neighbors[i] != nullptr && dynamic_cast<Mine*>(neighbors[i])) {
                numNeighborMines++;
            }
        }
        if (numNeighborMines == 0) {
            for (Tile* neighborTile : neighbors) {
                if (neighborTile) {
                    neighborTile->onClickLeft();
                }
            }
        }
    }
}
