#include "minesweeper.h"
#include "Toolbox.h"
#include <iostream>
#include <cmath>
using namespace std;

// in order to change dimensions, please change line 13 in toolbox.h (sf::Vector2i boardDimensions = sf::Vector2i(25, 16);). please change the dimensions for sf::Vector2i(x,y). Thanks!
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
                // new game button
                if (event.mouseButton.button == sf::Mouse::Left && mousePosition.x >= 368 && mousePosition.x <= 368 + 64 &&
                    mousePosition.y >= 512 && mousePosition.y <= 512 + 64) {
                    toolbox.newGameButton->onClick();
                } // debug button
                else if (mousePosition.x >= 496 && mousePosition.x <= 496 + 64 &&
                           mousePosition.y >= 512 && mousePosition.y <= 512 + 64) {
                    toolbox.debugButton->onClick();
                } // test button 1
                else if (mousePosition.x >= 560 && mousePosition.x <= 560 + 64 &&
                           mousePosition.y >= 512 && mousePosition.y <= 512 + 64) {
                    toolbox.testButton1->onClick();
                } // test button 2
                else if (mousePosition.x >= 624 && mousePosition.x <= 624 + 64 &&
                           mousePosition.y >= 512 && mousePosition.y <= 512 + 64) {
                    toolbox.testButton2->onClick();
                } // test button 3
                else if (mousePosition.x >= 688 && mousePosition.x <= 688 + 64 &&
                           mousePosition.y >= 512 && mousePosition.y <= 512 + 64) {
                    toolbox.testButton3->onClick();
                } else {
                    // check tiles for clicking if game is still being played
                    for (int y = 0; y < toolbox.boardDimensions.x; ++y) {
                        for (int x = 0; x < toolbox.boardDimensions.y; ++x) {
                            Tile *currentTile = toolbox.gameState->getTile(x, y);
                            if (mousePosition.x >= currentTile->getLocation().x &&
                                mousePosition.x <= currentTile->getLocation().x + 32 &&
                                mousePosition.y >= currentTile->getLocation().y &&
                                mousePosition.y <= currentTile->getLocation().y + 32 && toolbox.gameState->getPlayStatus() != GameState::LOSS) {
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
void loadTestButton1() {
    Toolbox& toolbox = Toolbox::getInstance();
    delete toolbox.gameState;
    toolbox.gameState = new GameState("boards/testboard1.brd");
}
void loadTestButton2() {
    Toolbox& toolbox = Toolbox::getInstance();
    delete toolbox.gameState;
    toolbox.gameState = new GameState("boards/testboard2.brd");
}
void loadTestButton3() {
    Toolbox& toolbox = Toolbox::getInstance();
    delete toolbox.gameState;
    toolbox.gameState = new GameState("boards/testboard3.brd");
}
void restart() {
    Toolbox& toolbox = Toolbox::getInstance();
    delete toolbox.gameState;
    toolbox.gameState = new GameState();
    toolbox.debugMode = false;
    toolbox.originalMineStates.clear();
}
void render() {
    Toolbox& toolbox = Toolbox::getInstance();
    // calculation to check win
    int numRevealed = 0;
    for (int y = 0; y < toolbox.boardDimensions.x; y++) {
        for (int x = 0; x < toolbox.boardDimensions.y; x++) {
            Tile* currentTile = toolbox.gameState->getTile(x, y);
            if (typeid(*currentTile) == typeid(Tile) && currentTile->getState() == Tile::REVEALED) {
                numRevealed++;
            }
        }
    }
    if ((numRevealed + toolbox.gameState->getMineCount()) == toolbox.boardDimensions.x * toolbox.boardDimensions.y) {
        toolbox.gameState->setPlayStatus(GameState::WIN);
    }
    // display tiles
    for (int y = 0; y < toolbox.boardDimensions.x; y++) {
        for (int x = 0; x < toolbox.boardDimensions.y; x++) {
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
    // display mine counter (sorry in advance)
    int mineDisplay = toolbox.gameState->getMineCount() - toolbox.gameState->getFlagCount();
    int absMineDisplay = std::abs(mineDisplay);
    int onesDig = absMineDisplay % 10;
    absMineDisplay = absMineDisplay / 10;
    int tensDig = absMineDisplay % 10;
    sf::Texture oneDigImg;
    sf::IntRect textureRect;
    // set digit for ones
    switch (onesDig) {
        case 0:
            // Define the rectangle that represents the part of the image you want
            textureRect = sf::IntRect(0, 0, 21, 32); // (left, top, width, height)
            // Create a new texture using only the specified part
            oneDigImg.loadFromImage(toolbox.digits.copyToImage(), textureRect);
            break;
        case 1:
            textureRect = sf::IntRect(21, 0, 21, 32); // (left, top, width, height)
            oneDigImg.loadFromImage(toolbox.digits.copyToImage(), textureRect);
            break;
        case 2:
            textureRect = sf::IntRect(42, 0, 21, 32); // (left, top, width, height)
            oneDigImg.loadFromImage(toolbox.digits.copyToImage(), textureRect);
            break;
        case 3:
            textureRect = sf::IntRect(63, 0, 21, 32); // (left, top, width, height)
            oneDigImg.loadFromImage(toolbox.digits.copyToImage(), textureRect);
            break;
        case 4:
            textureRect = sf::IntRect(84, 0, 21, 32); // (left, top, width, height)
            oneDigImg.loadFromImage(toolbox.digits.copyToImage(), textureRect);
            break;
        case 5:
            textureRect = sf::IntRect(105, 0, 21, 32); // (left, top, width, height)
            oneDigImg.loadFromImage(toolbox.digits.copyToImage(), textureRect);
            break;
        case 6:
            textureRect = sf::IntRect(126, 0, 21, 32); // (left, top, width, height)
            oneDigImg.loadFromImage(toolbox.digits.copyToImage(), textureRect);
            break;
        case 7:
            textureRect = sf::IntRect(147, 0, 21, 32); // (left, top, width, height)
            oneDigImg.loadFromImage(toolbox.digits.copyToImage(), textureRect);
            break;
        case 8:
            textureRect = sf::IntRect(168, 0, 21, 32); // (left, top, width, height)
            oneDigImg.loadFromImage(toolbox.digits.copyToImage(), textureRect);
            break;
        case 9:
            textureRect = sf::IntRect(189, 0, 21, 32); // (left, top, width, height)
            oneDigImg.loadFromImage(toolbox.digits.copyToImage(), textureRect);
            break;
    }
    // set for tens digit
    sf::Texture tensDigImg;
    sf::IntRect tensTextureRect;
    switch (tensDig) {
        case 0:
            // Define the rectangle that represents the part of the image you want
            tensTextureRect = sf::IntRect(0, 0, 21, 32); // (left, top, width, height)
            // Create a new texture using only the specified part
            tensDigImg.loadFromImage(toolbox.digits.copyToImage(), tensTextureRect);
            break;
        case 1:
            tensTextureRect = sf::IntRect(21, 0, 21, 32); // (left, top, width, height)
            tensDigImg.loadFromImage(toolbox.digits.copyToImage(), tensTextureRect);
            break;
        case 2:
            tensTextureRect = sf::IntRect(42, 0, 21, 32); // (left, top, width, height)
            tensDigImg.loadFromImage(toolbox.digits.copyToImage(), tensTextureRect);
            break;
        case 3:
            tensTextureRect = sf::IntRect(63, 0, 21, 32); // (left, top, width, height)
            tensDigImg.loadFromImage(toolbox.digits.copyToImage(), tensTextureRect);
            break;
        case 4:
            tensTextureRect = sf::IntRect(84, 0, 21, 32); // (left, top, width, height)
            tensDigImg.loadFromImage(toolbox.digits.copyToImage(), tensTextureRect);
            break;
        case 5:
            tensTextureRect = sf::IntRect(105, 0, 21, 32); // (left, top, width, height)
            tensDigImg.loadFromImage(toolbox.digits.copyToImage(), tensTextureRect);
            break;
        case 6:
            tensTextureRect = sf::IntRect(126, 0, 21, 32); // (left, top, width, height)
            tensDigImg.loadFromImage(toolbox.digits.copyToImage(), tensTextureRect);
            break;
        case 7:
            tensTextureRect = sf::IntRect(147, 0, 21, 32); // (left, top, width, height)
            tensDigImg.loadFromImage(toolbox.digits.copyToImage(), tensTextureRect);
            break;
        case 8:
            tensTextureRect = sf::IntRect(168, 0, 21, 32); // (left, top, width, height)
            tensDigImg.loadFromImage(toolbox.digits.copyToImage(), tensTextureRect);
            break;
        case 9:
            tensTextureRect = sf::IntRect(189, 0, 21, 32); // (left, top, width, height)
            tensDigImg.loadFromImage(toolbox.digits.copyToImage(), tensTextureRect);
            break;
    }
    // check if 3-digit number, then set for hundreds digit if needed
    absMineDisplay = absMineDisplay / 10;
    if (std::abs(mineDisplay) > 99) {
        int hundsDig = absMineDisplay % 10;
        sf::Texture hundsDigImg;
        sf::IntRect hundsTextureRect;
        switch (hundsDig) {
            case 0:
                // Define the rectangle that represents the part of the image you want
                hundsTextureRect = sf::IntRect(0, 0, 21, 32); // (left, top, width, height)
                // Create a new texture using only the specified part
                hundsDigImg.loadFromImage(toolbox.digits.copyToImage(), hundsTextureRect);
                break;
            case 1:
                hundsTextureRect = sf::IntRect(21, 0, 21, 32); // (left, top, width, height)
                hundsDigImg.loadFromImage(toolbox.digits.copyToImage(), hundsTextureRect);
                break;
            case 2:
                hundsTextureRect = sf::IntRect(42, 0, 21, 32); // (left, top, width, height)
                hundsDigImg.loadFromImage(toolbox.digits.copyToImage(), hundsTextureRect);
                break;
            case 3:
                hundsTextureRect = sf::IntRect(63, 0, 21, 32); // (left, top, width, height)
                hundsDigImg.loadFromImage(toolbox.digits.copyToImage(), hundsTextureRect);
                break;
            case 4:
                hundsTextureRect = sf::IntRect(84, 0, 21, 32); // (left, top, width, height)
                hundsDigImg.loadFromImage(toolbox.digits.copyToImage(), hundsTextureRect);
                break;
            case 5:
                hundsTextureRect = sf::IntRect(105, 0, 21, 32); // (left, top, width, height)
                hundsDigImg.loadFromImage(toolbox.digits.copyToImage(), hundsTextureRect);
                break;
            case 6:
                hundsTextureRect = sf::IntRect(126, 0, 21, 32); // (left, top, width, height)
                hundsDigImg.loadFromImage(toolbox.digits.copyToImage(), hundsTextureRect);
                break;
            case 7:
                hundsTextureRect = sf::IntRect(147, 0, 21, 32); // (left, top, width, height)
                hundsDigImg.loadFromImage(toolbox.digits.copyToImage(), hundsTextureRect);
                break;
            case 8:
                hundsTextureRect = sf::IntRect(168, 0, 21, 32); // (left, top, width, height)
                hundsDigImg.loadFromImage(toolbox.digits.copyToImage(), hundsTextureRect);
                break;
            case 9:
                hundsTextureRect = sf::IntRect(189, 0, 21, 32); // (left, top, width, height)
                hundsDigImg.loadFromImage(toolbox.digits.copyToImage(), hundsTextureRect);
                break;
        }
        sf::Sprite sprite3(hundsDigImg);
        sprite3.setPosition(0, 512);
        toolbox.window.draw(sprite3);
    } // not three digit number
    else {
        // check if negative, set "hundreds digit" to negative or 0 based on that
        sf::IntRect negTextureRect;
        sf::Texture negDigImg;
        if (mineDisplay < 0) {
            negTextureRect = sf::IntRect(210, 0, 21, 32);
            negDigImg.loadFromImage(toolbox.digits.copyToImage(), negTextureRect);
            sf::Sprite sprite3(negDigImg);
            sprite3.setPosition(0, 512);
            toolbox.window.draw(sprite3);
        } else {
            negTextureRect = sf::IntRect(0, 0, 21, 32);
            negDigImg.loadFromImage(toolbox.digits.copyToImage(), negTextureRect);
            sf::Sprite sprite3(negDigImg);
            sprite3.setPosition(0, 512);
            toolbox.window.draw(sprite3);
        }
    }
    // draw ones and tens digits
    sf::Sprite sprite(oneDigImg);
    sprite.setPosition(42, 512);
    toolbox.window.draw(sprite);
    sf::Sprite sprite2(tensDigImg);
    sprite2.setPosition(21, 512);
    toolbox.window.draw(sprite2);

    //display buttons
    toolbox.debugButton->getSprite()->setPosition(496,512);
    toolbox.window.draw(*toolbox.debugButton->getSprite());
    toolbox.testButton1->getSprite()->setPosition(560,512);
    toolbox.window.draw(*toolbox.testButton1->getSprite());
    toolbox.testButton2->getSprite()->setPosition(624,512);
    toolbox.window.draw(*toolbox.testButton2->getSprite());
    toolbox.testButton3->getSprite()->setPosition(688,512);
    toolbox.window.draw(*toolbox.testButton3->getSprite());
    toolbox.window.display();
}

void toggleDebugMode() {
    Toolbox& toolbox = Toolbox::getInstance();
    if (!getDebugMode()) {
        toolbox.debugMode = true;
    }
    else {
        toolbox.debugMode = false;
    }
    if (getDebugMode()) {
        // store original states for only mines
        toolbox.originalMineStates.clear();
        for (int y = 0; y < toolbox.boardDimensions.x; ++y) {
            for (int x = 0; x < toolbox.boardDimensions.y; ++x) {
                Tile* currentTile = toolbox.gameState->getTile(x, y);
                if (auto mine = dynamic_cast<Mine*>(currentTile)) {
                    toolbox.originalMineStates.push_back({x, y, mine->getState()});
                    mine->setState(Tile::REVEALED);
                }
            }
        }
    } else {
        // restore original states after debug mode for mines
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
