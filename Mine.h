#pragma once

#include <array>
#include "Tile.h"

class Mine : public Tile {
public:
    explicit Mine(sf::Vector2f position);
    void setState(State _state) override;
    State getState() override;
    void setNeighbors(std::array<Mine*, 8> _neighbors);
    void onClickLeft() override;
    void onClickRight() override;
    void draw() override;

private:
    bool hasMine;
    State state;
    sf::Vector2f coordinate;
    std::array<Mine*, 8> neighbors;
};

