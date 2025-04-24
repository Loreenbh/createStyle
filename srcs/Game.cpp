#include "Game.hpp"

//*****************************************************************CONSTRUCTOR
Game::Game() : 
    _state(MENU), _graphics(nullptr){
    try{
        _graphics = new Graphic(100, 100); //rien a verifier
        _graphics->createWindow(); //check fenetre closed
        _graphics->initGraphicMenu(); //creation de scene Menu
        _graphics->initGraphicHelp(); //creation de scene Help
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

//*****************************************************************PUBLIC METHODS

if (game->getStatus() == MENU){
    game->selectEventMenu();
    // game->hoverButtonsMenu();
    // if (game->getEvent().type == sf::Event::MouseButtonPressed)
    //     game->checkButtonMenuPressed(); //ici je change le set le type
}


void Game::selectEventMenu(){
    if (game->hoverButtonsMenu()) //si ca me true, l animation s arret
}


void Game::checkButtonMenuPressed(void){
    sf::Vector2i mousePos = sf::Mouse::getPosition(this->getGraphic()->getWindow());
    if (this->getGraphic()->getGraphicMenu()->getButtonHelp().getGlobalBounds().contains(mousePos.x, mousePos.y))
        this->setStatus(HELP);
    else if (this->getGraphic()->getGraphicMenu()->getButtonPlay().getGlobalBounds().contains(mousePos.x, mousePos.y))
        this->setStatus(PLAY);
}

bool Game::hoverButtonsMenu(){
    sf::Vector2i mousePos = sf::Mouse::getPosition(this->_graphics->getWindow());
    if (this->_graphics->getGraphicMenu()->getButtonPlay().getGlobalBounds().contains(mousePos.x, mousePos.y))
        this->_graphics->getGraphicMenu()->getButtonPlay().setFillColor(sf::Color::Red);
    else if (this->_graphics->getGraphicMenu()->getButtonHelp().getGlobalBounds().contains(mousePos.x, mousePos.y))
        this->_graphics->getGraphicMenu()->getButtonHelp().setFillColor(sf::Color::Green);
    else{
        this->_graphics->getGraphicMenu()->getButtonPlay().setFillColor(sf::Color::White);
        this->_graphics->getGraphicMenu()->getButtonHelp().setFillColor(sf::Color::White);
        return (false);
    }
    return (true); //ici je return un setters
}


void Game::closeWindow(){
    this->_graphics->getWindow().close();
}

//*****************************************************************GETTERS
Graphic *Game::getGraphic() const{
    return (this->_graphics);
}

GameState Game::getStatus() const{
    return (this->_state);
}

sf::Event &Game::getEvent(){
    return (this->_event);
}

//*****************************************************************SETTERS
GameState Game::setStatus(GameState status){
    this->_state = status;
    return (this->_state);
}

