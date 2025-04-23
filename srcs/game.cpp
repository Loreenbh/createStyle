#include "game.hpp"

// //Constructor
Game::Game() : 
    _state(MENU), _graphics(nullptr){
    try{
        _graphics = new Graphic(100, 100); //rien a verifier
        _graphics->createWindow(); //check fenetre closed
        _graphics->initGraphicMenu(); //creation de scene Menu
    }
    catch(std::exception &e){
        throw;
    }
    std::cout << "Game created" << std::endl;
}

Game::~Game(){
    delete _graphics;
    std::cout << "Game destroyed" << std::endl;
}

//Public Methods


//Getters
Graphic *Game::getGraphic() const{
    return (this->_graphics);
}

GameState Game::getStatus() const{
    return (this->_state);
}