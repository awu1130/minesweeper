#include "minesweeper.h"
#include "Toolbox.h"
#include <iostream>
using namespace std;

bool debugMode = false;
std::vector<std::array<int, 3>> originalMineStates; // Store original mine states

int launch() {
    render();
    return 0;
}
void restart() {

}
void render() {
    // Main loop
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
                    delete toolbox.gameState;
                    // Create a new game state
                    toolbox.gameState = new GameState();
                    // Reset debug mode and original states
                    debugMode = false;
                    originalMineStates.clear();
                } else if (mousePosition.x >= 496 && mousePosition.x <= 496 + 64 &&
                           mousePosition.y >= 512 && mousePosition.y <= 512 + 64) {
                    // Handle click on the debug button
                    toggleDebugMode();
                    if (debugMode == true) {
                        // Store original states if entering debug mode
                        originalMineStates.clear();
                        for (int y = 0; y < 25; ++y) {
                            for (int x = 0; x < 16; ++x) {
                                Tile* currentTile = toolbox.gameState->getTile(x, y);
                                if (auto mine = dynamic_cast<Mine*>(currentTile)) {
                                    originalMineStates.push_back({x, y, mine->getState()});
                                    mine->setState(Tile::EXPLODED);
                                }
                            }
                        }
                    } else {
                        // Restore original states when exiting debug mode
                        for (const auto& mineState : originalMineStates) {
                            int x = mineState[0];
                            int y = mineState[1];
                            Tile* currentTile = toolbox.gameState->getTile(x, y);
                            if (auto mine = dynamic_cast<Mine*>(currentTile)) {
                                mine->setState((Tile::State) mineState[2]);
                            }
                        }
                        originalMineStates.clear();
                    }
            } else if (mousePosition.x >= 560 && mousePosition.x <= 560 + 64 &&
                           mousePosition.y >= 512 && mousePosition.y <= 512 + 64) {
                    // Handle click on test button 1
                    toolbox.gameState = new GameState("./boards/testboard1.brd");
                } else if (mousePosition.x >= 624 && mousePosition.x <= 624 + 64 &&
                           mousePosition.y >= 512 && mousePosition.y <= 512 + 64) {
                    // Handle click on test button 2
                    // ...
                } else {
                    // The click is not on any button, so it must be on a tile
                    // Iterate over tiles and check for left/right-click on each tile
                    for (int y = 0; y < 25; ++y) {
                        for (int x = 0; x < 16; ++x) {
                            Tile *currentTile = toolbox.gameState->getTile(x, y);
                            if (mousePosition.x >= currentTile->getLocation().x &&
                                mousePosition.x <= currentTile->getLocation().x + 32 &&
                                mousePosition.y >= currentTile->getLocation().y &&
                                mousePosition.y <= currentTile->getLocation().y + 32) {
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
        // display tiles
        for (int y = 0; y < 25; ++y) {
            for (int x = 0; x < 16; ++x) {
                toolbox.gameState->getTile(x, y)->draw();
            }
        }
        // display buttons
        toolbox.newGameButton->getSprite()->setPosition(368,512);
        toolbox.window.draw(*toolbox.newGameButton->getSprite());
        toolbox.debugButton->getSprite()->setPosition(496,512);
        toolbox.window.draw(*toolbox.debugButton->getSprite());
        toolbox.testButton1->getSprite()->setPosition(560,512);
        toolbox.window.draw(*toolbox.testButton1->getSprite());
        toolbox.testButton2->getSprite()->setPosition(624,512);
        toolbox.window.draw(*toolbox.testButton2->getSprite());

        toolbox.window.display();
    }
}
void toggleDebugMode() {
    if (!debugMode) {
        debugMode = true;
    }
    else {
        debugMode = false;
    }
}
bool getDebugMode(){
    return debugMode;
}

int main() {
    launch();
}
