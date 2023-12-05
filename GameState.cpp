#include "GameState.h"
#include <random>
#include <vector>
#include <iostream>
#include <array>
#include <fstream>

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
    // create vectors
    for (int y = 0; y < _dimensions.y; y++) {
        for (int x = 0; x < _dimensions.x; x++) {
            if (y - 1 >= 0 && x - 1 >= 0) {
                neighbors[0] = board[y - 1][x - 1].get();
            } else {
                neighbors[0] = nullptr;
            }
            if (y - 1 >= 0) {
                neighbors[1] = board[y - 1][x].get();
            } else {
                neighbors[1] = nullptr;
            }
            if (y - 1 >= 0 && x + 1 < _dimensions.x) {
                neighbors[2] = board[y - 1][x + 1].get();
            } else {
                neighbors[2] = nullptr;
            }
            if (x - 1 >= 0) {
                neighbors[3] = board[y][x - 1].get();
            } else {
                neighbors[3] = nullptr;
            }
            if (x + 1 < _dimensions.x) {
                neighbors[4] = board[y][x + 1].get();
            } else {
                neighbors[4] = nullptr;
            }
            if (y + 1 < _dimensions.y && x - 1 >= 0) {
                neighbors[5] = board[y + 1][x - 1].get();
            } else {
                neighbors[5] = nullptr;
            }
            if (y + 1 < _dimensions.y) {
                neighbors[6] = board[y + 1][x].get();
            } else {
                neighbors[6] = nullptr;
            }
            if (y + 1 < _dimensions.y && x + 1 < _dimensions.x) {
                neighbors[7] = board[y + 1][x + 1].get();
            } else {
                neighbors[7] = nullptr;
            }
            board[y][x]->setNeighbors(neighbors);
        }
    }
}

GameState::GameState(const char* filepath) {
    // taken from my lab 8
    Toolbox& toolbox = Toolbox::getInstance();
    ifstream file(filepath);
    int i = 0;
    if (file.is_open()) {
        std::string fileContent;
        std::string line;
        toolbox.dimensionsX = line.length();
        cout<<toolbox.dimensionsX;
        // loop that reads every line into fileContent
        while (std::getline(file, line)) {
            i++;
            fileContent += line + "\n";
        }
        cout<<fileContent;
    }
    toolbox.dimensionsY = i;
    cout<<toolbox.dimensionsY;
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


