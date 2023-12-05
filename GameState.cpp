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
    numFlags = 0;
    numMines = _numberOfMines;
    std::array<Tile*, 8> neighbors{};

    // create the 2D vector with tile objects
    for (int y = 0; y < _dimensions.y; y++) {
        board.emplace_back();  // Emplace a new row
        auto& currentRow = board.back();
        for (int x = 0; x < _dimensions.x; x++) {
            currentRow.emplace_back(std::make_unique<Tile>(sf::Vector2f(float(x) * 32.0f, float(y) * 32.0f)));
        }
    }
    // create mines
    for (int i = 0; i < _numberOfMines; i++) {
        double randomY = yDistribution(gen);
        double randomX = xDistribution(gen);
        board[randomY][randomX] = std::make_unique<Mine>(sf::Vector2f (int(randomX) * 32.0f, int(randomY) * 32.0f));
    }
    // create neighbors
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
    // reading file part taken from my lab 8
    std::array<Tile*, 8> neighbors{};
    cout<<"n";
    int dimensionX;
    int dimensionY;
    std::vector<vector<char>> fileDigits;
    cout<<"j";
    ifstream file(filepath);
    if (file.is_open()) {
        cout<<"m";
        std::string fileContent;
        std::string line;
        //x = line.length();
        // loop that reads every line into fileContent
        while (std::getline(file, line)) {
            dimensionX = line.length();
            std::vector<char> row;
            for (int i = 0; i < dimensionX; i++) {
                row.push_back(line[i]);
            }
            fileDigits.push_back(row);
            dimensionY++;
        }
    }
    // create the 2d vector with tile objects
    cout<<"P";

    board.resize(dimensionY);
    for (int y = 0; y < dimensionY; y++) {
        cout<<"K";
        board[y].resize(dimensionX);
        for (int x = 0; x < dimensionX; x++) {
            cout<<"T";
            if (fileDigits[y][x] == '0') {
                board[y][x] = std::make_unique<Tile>(sf::Vector2f(float(x) * 32.0f, float(y) * 32.0f));
            } else {
                board[y][x] = std::make_unique<Mine>(sf::Vector2f (int(x) * 32.0f, int(y) * 32.0f));
            }
        }
    }
    cout<<"B";
    // create neighbors
    for (int y = 0; y < dimensionY; y++) {
        cout<<"G";
        for (int x = 0; x < dimensionX; x++) {
            cout<<"R";
            if (y - 1 >= 0 && x - 1 >= 0) {
                neighbors[0] = board[y - 1][x - 1].get();
                cout<<"0";
            } else {
                neighbors[0] = nullptr;
                cout<<"1";
            }
            if (y - 1 >= 0) {
                neighbors[1] = board[y - 1][x].get();
                cout<<"2";
            } else {
                neighbors[1] = nullptr;
                cout<<"3";
            }
            if (y - 1 >= 0 && x + 1 < dimensionX) {
                neighbors[2] = board[y - 1][x + 1].get();
                cout<<"4";
            } else {
                neighbors[2] = nullptr;
                cout<<"5";
            }
            if (x - 1 >= 0) {
                neighbors[3] = board[y][x - 1].get();
                cout<<"6";
            } else {
                neighbors[3] = nullptr;
                cout<<"7";
            }
            if (x + 1 < dimensionX) {
                neighbors[4] = board[y][x + 1].get();
                cout<<"8";
            } else {
                neighbors[4] = nullptr;
                cout<<"9";
            }
            if (y + 1 < dimensionY && x - 1 >= 0) {
                neighbors[5] = board[y + 1][x - 1].get();
                cout<<"10";
            } else {
                neighbors[5] = nullptr;
                cout<<"11";
            }
            if (y + 1 < dimensionY) {
                neighbors[6] = board[y + 1][x].get();
                cout<<"12";
            } else {
                neighbors[6] = nullptr;
                cout<<"13";
            }
            if (y + 1 < dimensionY && x + 1 < dimensionX) {
                neighbors[7] = board[y + 1][x + 1].get();
                cout<<"14";
            } else {
                neighbors[7] = nullptr;
                cout<<"15";
            }
            board[y][x]->setNeighbors(neighbors);
        }
    }
    cout<<"W"<<endl;
}
int GameState::getFlagCount() {
    numFlags = 0;
    int numRows = board.size();
    int numCols = (numRows > 0) ? board[0].size() : 0;
    for (int y = 0; y < numRows; ++y) {
        for (int x = 0; x < numCols; ++x) {
            if (board[y][x]->getState() == Tile::FLAGGED) {
                numFlags++;
            }
        }
    }
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


