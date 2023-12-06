#include "Toolbox.h"
#include <iostream>

// Constructor
Toolbox::Toolbox() {
    // set window
    window.create(sf::VideoMode(800, 600), "P4 - Minesweeper, Angelina Wu");
    // set textures
    hiddenTile.loadFromFile("images/tile_hidden.png");
    flag.loadFromFile("images/flag.png");
    revealedTile.loadFromFile("images/tile_revealed.png");
    mine.loadFromFile("images/mine.png");
    buttonTest1.loadFromFile("images/test_1.png");
    buttonTest2.loadFromFile("images/test_2.png");
    buttonTest3.loadFromFile("images/Test_3.png");
    buttonDebug.loadFromFile("images/debug.png");
    faceLose.loadFromFile("images/face_lose.png");
    faceWin.loadFromFile("images/face_win.png");
    faceHappy.loadFromFile("images/face_happy.png");
    number1.loadFromFile("images/number_1.png");
    number2.loadFromFile("images/number_2.png");
    number3.loadFromFile("images/number_3.png");
    number4.loadFromFile("images/number_4.png");
    number5.loadFromFile("images/number_5.png");
    number6.loadFromFile("images/number_6.png");
    number7.loadFromFile("images/number_7.png");
    number8.loadFromFile("images/number_8.png");
    digits.loadFromFile("images/digits.png");
    // create gameState
    gameState = new GameState(boardDimensions);
    // creating debugbutton
    debugButton = new Button(sf::Vector2f(), toggleDebugMode);
    sf::Sprite* spriteButtonDebug = new sf::Sprite(buttonDebug);
    debugButton->setSprite(spriteButtonDebug);
    spriteButtonDebug->setPosition(debugButton->getPosition());
    // make newgamebutton
    newGameButton = new Button(sf::Vector2f(), restart);
    spriteFaceHappy = new sf::Sprite(faceHappy);
    spriteFaceLose = new sf::Sprite(faceLose);
    spriteFaceWin = new sf::Sprite(faceWin);
    newGameButton->setSprite(spriteFaceHappy);
    spriteFaceHappy->setPosition(newGameButton->getPosition());
    // testbutton1
    testButton1 = new Button(sf::Vector2f(), loadTestButton1);
    sf::Sprite* spriteButtonTest1 = new sf::Sprite(buttonTest1);
    testButton1->setSprite(spriteButtonTest1);
    spriteButtonTest1->setPosition(testButton1->getPosition());
    // testbutton2
    testButton2 = new Button(sf::Vector2f(), loadTestButton2);
    sf::Sprite* spriteButtonTest2 = new sf::Sprite(buttonTest2);
    testButton2->setSprite(spriteButtonTest2);
    spriteButtonTest2->setPosition(newGameButton->getPosition());
    // testbutton3
    testButton3 = new Button(sf::Vector2f(), loadTestButton3);
    sf::Sprite* spriteButtonTest3 = new sf::Sprite(buttonTest3);
    testButton3->setSprite(spriteButtonTest3);
    spriteButtonTest2->setPosition(newGameButton->getPosition());
}
// singleton ensures instance is created only once
Toolbox& Toolbox::getInstance() {
    static Toolbox instance;
    return instance;
}
