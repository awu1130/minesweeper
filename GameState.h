#pragma once
#include <SFML/Graphics.hpp>
#include "Toolbox.h"
#include "Tile.h"
#include "Mine.h"
#include <memory>
using namespace std;

class GameState {
public:
    enum PlayStatus { WIN, LOSS, PLAYING };
    explicit GameState(sf::Vector2i _dimensions = sf::Vector2i(25, 16), int _numberOfMines = 50);
    explicit GameState(const char* filepath);
    int getFlagCount();
    int getMineCount();
    Tile* getTile(int x, int y);
    PlayStatus getPlayStatus();
    void setPlayStatus(PlayStatus _status);
private:
    PlayStatus playStatus;
    std::vector<std::vector<std::unique_ptr<Tile>>> board;
    //vector<vector<Mine>> mineBoard;
    int numFlags;
    int numMines;
};


