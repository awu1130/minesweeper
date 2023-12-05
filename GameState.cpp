#include "GameState.h"
#include <random>
#include <vector>
#include <iostream>
#include <array>
#include <fstream>
#include <set>

GameState::GameState(sf::Vector2i _dimensions, int _numberOfMines) {
    // Seed the random number generator with the current time
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> yDistribution(0, _dimensions.y);
    std::uniform_real_distribution<double> xDistribution(0, _dimensions.x);
    // store unique random positions
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
    // Set to store unique random positions
    std::set<std::pair<int, int>> uniquePositions;

    // Create mines
    for (int i = 0; i < _numberOfMines; i++) {
        double randomY;
        double randomX;
        std::pair<int, int> position;
        // Generate unique random positions
        do {
            randomY = yDistribution(gen);
            randomX = xDistribution(gen);
            position = std::make_pair(static_cast<int>(randomY), static_cast<int>(randomX));
        } while (uniquePositions.count(position) > 0);
        uniquePositions.insert(position);
        // Create a Mine at the chosen position
        board[position.first][position.second] = std::make_unique<Mine>(sf::Vector2f(int(randomX) * 32.0f, int(randomY) * 32.0f));
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
    playStatus = PLAYING;
    std::array<Tile*, 8> neighbors{};
    int dimensionX = 0;
    int dimensionY = 0;
    std::vector<vector<char>> fileDigits;
    ifstream file(filepath);
    if (file.is_open()) {
        std::string line;
        // Read the first line separately
        if (std::getline(file, line)) {
            dimensionX = line.length();
            std::vector<char> row;
            for (int i = 0; i < dimensionX; i++) {
                row.push_back(line[i]);
            }
            fileDigits.push_back(row);
            dimensionY++;
        }
        // Loop that reads every remaining line into fileContent
        while (std::getline(file, line)) {
            cout << dimensionX << endl;
            // Check if the line is not empty before processing
            if (!line.empty()) {
                std::vector<char> row;
                for (int i = 0; i < dimensionX; i++) {
                    row.push_back(line[i]);
                }
                fileDigits.push_back(row);
                dimensionY++;
            }
        }
    }
    // create the 2d vector with tile objects
    board.resize(dimensionY);
    for (int y = 0; y < dimensionY; y++) {
        board[y].resize(dimensionX);
        for (int x = 0; x < dimensionX; x++) {
            if (fileDigits[y][x] == '0') {
                board[y][x] = std::make_unique<Tile>(sf::Vector2f(float(x) * 32.0f, float(y) * 32.0f));
            } else {
                board[y][x] = std::make_unique<Mine>(sf::Vector2f (float(x) * 32.0f, float(y) * 32.0f));
                numMines++;
            }
        }
    }
    std::cout<<numMines<<endl;
    // create neighbors
    for (int y = 0; y < dimensionY; y++) {
        for (int x = 0; x < dimensionX; x++) {
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
            if (y - 1 >= 0 && x + 1 < dimensionX) {
                neighbors[2] = board[y - 1][x + 1].get();
            } else {
                neighbors[2] = nullptr;
            }
            if (x - 1 >= 0) {
                neighbors[3] = board[y][x - 1].get();
            } else {
                neighbors[3] = nullptr;
            }
            if (x + 1 < dimensionX) {
                neighbors[4] = board[y][x + 1].get();
            } else {
                neighbors[4] = nullptr;
            }
            if (y + 1 < dimensionY && x - 1 >= 0) {
                neighbors[5] = board[y + 1][x - 1].get();
            } else {
                neighbors[5] = nullptr;
            }
            if (y + 1 < dimensionY) {
                neighbors[6] = board[y + 1][x].get();
            } else {
                neighbors[6] = nullptr;
            }
            if (y + 1 < dimensionY && x + 1 < dimensionX) {
                neighbors[7] = board[y + 1][x + 1].get();
            } else {
                neighbors[7] = nullptr;
            }
            board[y][x]->setNeighbors(neighbors);
        }
    }
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


