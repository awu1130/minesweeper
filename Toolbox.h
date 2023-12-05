#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"
#include "minesweeper.h"
using namespace std;

class Toolbox {
public:
    bool debugMode;
    std::vector<std::array<int, 3>> originalMineStates; // Store original mine states

    sf::RenderWindow window; // SFML application window
    GameState* gameState; // Primary game state representation
    Button* debugButton; // Reveals mines in debug mode
    Button* newGameButton; // Resets / starts new game
    Button* loseButton;
    Button* testButton1; // Loads test board #1
    Button* testButton2; // Loads test board #2
    Button* testButton3; // Loads test board #2
    static Toolbox& getInstance();

    sf::Texture hiddenTile;
    sf::Texture flag;
    sf::Texture revealedTile;
    sf::Texture mine;
    sf::Texture buttonTest1;
    sf::Texture buttonTest2;
    sf::Texture buttonTest3;
    sf::Texture buttonDebug;
    sf::Texture faceLose;
    sf::Texture faceWin;
    sf::Texture faceHappy;
    sf::Texture number1;
    sf::Texture number2;
    sf::Texture number3;
    sf::Texture number4;
    sf::Texture number5;
    sf::Texture number6;
    sf::Texture number7;
    sf::Texture number8;
    sf::Texture digits;
    /*
    sf::Sprite spriteHiddenTile(sf::Texture texture);
    sf::Sprite spriteButtonTest1(sf::Texture texture);
    sf::Sprite spriteButtonTest2(sf::Texture texture);
    sf::Sprite spriteButtonDebug(sf::Texture texture);
    sf::Sprite spriteFaceLose(sf::Texture texture);
    sf::Sprite spriteFaceWin(sf::Texture texture);
    sf::Sprite spriteFaceHappy(sf::Texture texture); */
    sf::Sprite* spriteFaceHappy;
    sf::Sprite* spriteFaceLose;
    sf::Sprite* spriteFaceWin;
private:
    Toolbox();
};

