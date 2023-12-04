#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Button.h"
using namespace std;

class Toolbox {
public:
    sf::RenderWindow window; // SFML application window
    GameState* gameState; // Primary game state representation
    Button* debugButton; // Reveals mines in debug mode
    Button* newGameButton; // Resets / starts new game
    Button* testButton1; // Loads test board #1
    Button* testButton2; // Loads test board #2
    static Toolbox& getInstance();
    Button* debug;
    sf::Texture hiddenTile;
    sf::Texture flag;
    sf::Texture revealedTile;
    sf::Texture mine;
    sf::Texture buttonTest1;
    sf::Texture buttonTest2;
    sf::Texture buttonDebug;
    sf::Texture faceLose;
    sf::Texture faceWin;
    sf::Texture faceHappy;
    /*
    sf::Sprite spriteHiddenTile(sf::Texture texture);
    sf::Sprite spriteButtonTest1(sf::Texture texture);
    sf::Sprite spriteButtonTest2(sf::Texture texture);
    sf::Sprite spriteButtonDebug(sf::Texture texture);
    sf::Sprite spriteFaceLose(sf::Texture texture);
    sf::Sprite spriteFaceWin(sf::Texture texture);
    sf::Sprite spriteFaceHappy(sf::Texture texture); */
private:
    Toolbox();
};

