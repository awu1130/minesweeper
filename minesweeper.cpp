#include "minesweeper.h"
#include "Toolbox.h"
#include <iostream>
using namespace std;

int launch() {
    Toolbox& toolbox = Toolbox::getInstance();
    while (toolbox.window.isOpen()) {
        sf::Event event;
        while (toolbox.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                toolbox.window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition = toolbox.window.mapPixelToCoords(
                        sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                if (event.mouseButton.button == sf::Mouse::Left && mousePosition.x >= 368 && mousePosition.x <= 368 + 64 &&
                    mousePosition.y >= 512 && mousePosition.y <= 512 + 64) {
                    toolbox.newGameButton->onClick();
                } else if (mousePosition.x >= 496 && mousePosition.x <= 496 + 64 &&
                           mousePosition.y >= 512 && mousePosition.y <= 512 + 64) {
                    toolbox.debugButton->onClick();
                } else if (mousePosition.x >= 560 && mousePosition.x <= 560 + 64 &&
                           mousePosition.y >= 512 && mousePosition.y <= 512 + 64) {
                    // Handle click on test button 1
                    delete toolbox.gameState;
                    toolbox.gameState = new GameState("./boards/testboard1.brd");
                } else if (mousePosition.x >= 624 && mousePosition.x <= 624 + 64 &&
                           mousePosition.y >= 512 && mousePosition.y <= 512 + 64) {
                    // Handle click on test button 2
                    delete toolbox.gameState;
                    toolbox.gameState = new GameState("./boards/testboard2.brd");
                } else {
                    // The click is not on any button, so it must be on a tile
                    // Iterate over tiles and check for left/right-click on each tile
                    for (int y = 0; y < 25; ++y) {
                        for (int x = 0; x < 16; ++x) {
                            Tile *currentTile = toolbox.gameState->getTile(x, y);
                            if (mousePosition.x >= currentTile->getLocation().x &&
                                mousePosition.x <= currentTile->getLocation().x + 32 &&
                                mousePosition.y >= currentTile->getLocation().y &&
                                mousePosition.y <= currentTile->getLocation().y + 32 && toolbox.gameState->getPlayStatus() != GameState::LOSS) {
                                // Handle left/right-click on the current tile
                                if (event.mouseButton.button == sf::Mouse::Right) {
                                    currentTile->onClickRight();
                                } else if (event.mouseButton.button == sf::Mouse::Left) {
                                    currentTile->onClickLeft();
                                }
                            }
                        }
                    }
                }
            }
        }
        toolbox.window.clear(sf::Color::White);
        render();
    }
    return 0;
}
void restart() {
    Toolbox& toolbox = Toolbox::getInstance();
    delete toolbox.gameState;
    // Create a new game state
    toolbox.gameState = new GameState();
    // Reset debug mode and original states
    toolbox.debugMode = false;
    toolbox.originalMineStates.clear();
}
void render() {
    Toolbox& toolbox = Toolbox::getInstance();
    // display tiles
    for (int y = 0; y < 25; ++y) {
        for (int x = 0; x < 16; ++x) {
            toolbox.gameState->getTile(x, y)->draw();
        }
    }
    // display buttons
    if (toolbox.gameState->getPlayStatus() == GameState::LOSS) {
        toolbox.newGameButton->setSprite(toolbox.spriteFaceLose);
        toolbox.newGameButton->getSprite()->setPosition(368,512);
        toolbox.window.draw(*toolbox.newGameButton->getSprite());
    } else if (toolbox.gameState->getPlayStatus() == GameState::WIN) {
        toolbox.newGameButton->setSprite(toolbox.spriteFaceWin);
        toolbox.newGameButton->getSprite()->setPosition(368,512);
        toolbox.window.draw(*toolbox.newGameButton->getSprite());
    }
    else if (toolbox.gameState->getPlayStatus() == GameState::PLAYING){
        toolbox.newGameButton->setSprite(toolbox.spriteFaceHappy);
        toolbox.newGameButton->getSprite()->setPosition(368,512);
        toolbox.window.draw(*toolbox.newGameButton->getSprite());
    }
    toolbox.debugButton->getSprite()->setPosition(496,512);
    toolbox.window.draw(*toolbox.debugButton->getSprite());
    toolbox.testButton1->getSprite()->setPosition(560,512);
    toolbox.window.draw(*toolbox.testButton1->getSprite());
    toolbox.testButton2->getSprite()->setPosition(624,512);
    toolbox.window.draw(*toolbox.testButton2->getSprite());

    toolbox.window.display();
}

void toggleDebugMode() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (!toolbox.debugMode) {
        toolbox.debugMode = true;
    }
    else {
        toolbox.debugMode = false;
    }
    // Handle click on the debug button
    if (toolbox.debugMode) {
        // Store original states if entering debug mode
        toolbox.originalMineStates.clear();
        for (int y = 0; y < 25; ++y) {
            for (int x = 0; x < 16; ++x) {
                Tile* currentTile = toolbox.gameState->getTile(x, y);
                if (auto mine = dynamic_cast<Mine*>(currentTile)) {
                    toolbox.originalMineStates.push_back({x, y, mine->getState()});
                    mine->setState(Tile::REVEALED);
                }
            }
        }
    } else {
        // Restore original states when exiting debug mode
        for (const auto& mineState : toolbox.originalMineStates) {
            int x = mineState[0];
            int y = mineState[1];
            Tile* currentTile = toolbox.gameState->getTile(x, y);
            if (auto mine = dynamic_cast<Mine*>(currentTile)) {
                mine->setState((Tile::State) mineState[2]);
            }
        }
        toolbox.originalMineStates.clear();
    }
}
bool getDebugMode(){
    Toolbox& toolbox = Toolbox::getInstance();
    return toolbox.debugMode;
}

int main() {
    launch();
}
