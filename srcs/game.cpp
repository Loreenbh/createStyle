#include "game.hpp"

// //Constructor
Game::Game() : 
    _state(MENU), _graphics(nullptr){
    try{
        _graphics = new Graphic(800, 600);
        _graphics->createWindow();
        _graphics->loadBackgroundMenu();
    }
    catch(std::exception &e){
        throw;
    }
}

Game::~Game(){
    delete _graphics;
    std::cout << "L'objet Game a été détruit" << std::endl;
}

//Public Methods


//Getters
//Getters
Graphic *Game::getGraphic() const{
    return (this->_graphics);
}
