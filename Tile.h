#pragma once
#include <SFML/Graphics.hpp>
#include <array>
using namespace std;

class Tile {
protected:
    void revealNeighbors();

public:
    enum State { REVEALED, HIDDEN, FLAGGED, EXPLODED };
    Tile(sf::Vector2f position);
    sf::Vector2f getLocation();
    virtual State getState();
    std::array<Tile*, 8>& getNeighbors();
    virtual void setState(State _state);
    virtual void setNeighbors(std::array<Tile*, 8> _neighbors);
    virtual void onClickLeft();
    virtual void onClickRight();
    virtual void draw();
private:
    sf::Vector2f coordinate;
    State state;
    sf::Sprite sprite;
    std::array<Tile*, 8> neighbors;
    int numNeighborMines;
};





