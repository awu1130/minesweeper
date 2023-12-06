#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Mine.h"
#include <memory>
using namespace std;

class GameState {
public:
    enum PlayStatus { WIN, LOSS, PLAYING };
    GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    GameState(const char* filepath);
    int getFlagCount();
    int getMineCount();
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
private:
    PlayStatus playStatus;
    std::vector<std::vector<std::unique_ptr<Tile>>> board;
    int numFlags;
    // ensures numMines is reset when loading files
    int numMines = 0;
};


