#include "Toolbox.h"
#include <iostream>
//#include "Tile.cpp"
//#include "Button.cpp"

// Constructor
Toolbox::Toolbox() {
    // Initialize member variables here
    window.create(sf::VideoMode(800, 600), "P4 – Minesweeper, <Angelina Wu>");
    hiddenTile.loadFromFile("./images/tile_hidden.png");
    flag.loadFromFile("./images/flag.png");
    revealedTile.loadFromFile("./images/tile_revealed.png");
    mine.loadFromFile("./images/mine.png");
    buttonTest1.loadFromFile("./images/test_1.png");
    buttonTest2.loadFromFile("./images/test_2.png");
    buttonDebug.loadFromFile("./images/debug.png");
    faceLose.loadFromFile("./images/face_lose.png");
    faceWin.loadFromFile("./images/face_win.png");
    faceHappy.loadFromFile("./images/face_happy.png");
    number1.loadFromFile("./images/number_1.png");
    number2.loadFromFile("./images/number_1.png");
    number3.loadFromFile("./images/number_1.png");
    number4.loadFromFile("./images/number_1.png");
    number5.loadFromFile("./images/number_1.png");
    number6.loadFromFile("./images/number_1.png");
    number7.loadFromFile("./images/number_1.png");
    number8.loadFromFile("./images/number_1.png");
    // load files
    // dynamically allocate gameState
    gameState = new GameState();
    // Creating sprites for buttons
    debugButton = new Button(sf::Vector2f(300.0f, 100.0f), []() { std::cout << "Debug Button Clicked" << std::endl; });
    sf::Sprite* spriteButtonDebug = new sf::Sprite(buttonDebug);
    debugButton->setSprite(spriteButtonDebug);
    spriteButtonDebug->setPosition(debugButton->getPosition());

    newGameButton = new Button(sf::Vector2f(500.0f, 400.0f), []() { std::cout << "New Game Button Clicked" << std::endl; });
    sf::Sprite* spriteFaceHappy = new sf::Sprite(faceHappy);
    newGameButton->setSprite(spriteFaceHappy);
    spriteFaceHappy->setPosition(newGameButton->getPosition());

    testButton1 = new Button(sf::Vector2f(500.0f, 400.0f), []() { std::cout << "New Game Button Clicked" << std::endl; });
    sf::Sprite* spriteButtonTest1 = new sf::Sprite(buttonTest1);
    testButton1->setSprite(spriteButtonTest1);
    spriteButtonTest1->setPosition(testButton1->getPosition());

    testButton2 = new Button(sf::Vector2f(500.0f, 400.0f), []() { std::cout << "New Game Button Clicked" << std::endl; });
    sf::Sprite* spriteButtonTest2 = new sf::Sprite(buttonTest2);
    testButton2->setSprite(spriteButtonTest2);
    spriteButtonTest2->setPosition(newGameButton->getPosition());
}
// singleton ensures instance is created only once
Toolbox& Toolbox::getInstance() {
    static Toolbox instance;
    return instance;
}
// destructor
// Toolbox::~Toolbox() {
//     delete gameState;
//     delete debugButton;
//     delete newGameButton;
//     delete testButton1;
//     delete testButton2;
// }
