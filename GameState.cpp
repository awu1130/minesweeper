#include "GameState.h"
#include <random>
#include <vector>
#include <iostream>
#include <array>

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    // Seed the random number generator with the current time
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> yDistribution(0, _dimensions.y);
    std::uniform_real_distribution<double> xDistribution(0, _dimensions.x);

    playStatus = PLAYING;
    //numFlags = 0;
    numMines = 0;
    std::array<Tile*, 8> neighbors{};

    // create the 2d vector with tile objects
    board.resize(_dimensions.y);
    for (int y = 0; y < _dimensions.y; y++) {
        board[y].resize(_dimensions.x);
        for (int x = 0; x < _dimensions.x; x++) {
            board[y][x] = std::make_unique<Tile>(sf::Vector2f(float(x) * 32.0f, float(y) * 32.0f));
        }
    }
    // create mines
    for (numMines; numMines < _numberOfMines; numMines++) {
        double randomY = yDistribution(gen);
        double randomX = xDistribution(gen);
        board[randomY][randomX] = std::make_unique<Mine>(sf::Vector2f (int(randomX) * 32.0f, int(randomY) * 32.0f));
    }
    //int i = 0;
    for (int y = 0; y < _dimensions.y; y++) {
        for (int x = 0; x < _dimensions.x; x++) {
            if (y - 1 >= 0 && x - 1 >= 0) {
                neighbors[0] = board[y][x].get();
            } else {
                neighbors[0] = nullptr;
            }
            if (y >= 0 && x - 1 >= 0) {
                neighbors[1] = board[y][x].get();
            } else {
                neighbors[1] = nullptr;
            }
            if (y + 1 >= 0 && x - 1 >= 0) {
                neighbors[2] = board[y][x].get();
            } else {
                neighbors[2] = nullptr;
            }
            if (y - 1 >= 0 && x >= 0) {
                neighbors[3] = board[y][x].get();
            } else {
                neighbors[3] = nullptr;
            }
            if (y + 1 >= 0 && x >= 0) {
                neighbors[4] = board[y][x].get();
            } else {
                neighbors[4] = nullptr;
            }
            if (y - 1 >= 0 && x + 1 >= 0) {
                neighbors[5] = board[y][x].get();
            } else {
                neighbors[5] = nullptr;
            }
            if (y >= 0 && x + 1 >= 0) {
                neighbors[6] = board[y][x].get();
            } else {
                neighbors[6] = nullptr;
            }
            if (y + 1 >= 0 && x + 1 >= 0) {
                neighbors[7] = board[y][x].get();
            } else {
                neighbors[7] = nullptr;
            }
            board[y][x]->setNeighbors(neighbors);
            /*
            std::cout<<i;
            std::cout<<" ";
            i++;*/
        }
    }
}

GameState::GameState(const char* filepath) {

}
int GameState::getFlagCount() {
    return numFlags;
}
int GameState::getMineCount() {
    return numMines;
}
Tile* GameState::getTile(int x, int y) {
    return board[x][y].get();
}
GameState::PlayStatus GameState::getPlayStatus() {
    return playStatus;
}
void GameState::setPlayStatus(PlayStatus _status) {
    playStatus = _status;
}


