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

void Game::selectEventMenu(){
    this->hoverButtonsMenu(); //met a jour booleen animation
    if (this->getEvent().type == sf::Event::MouseButtonPressed)
        this->checkButtonMenuPressed();
}

void Game::selectEventHelp(){
    if (this->getEvent().type == sf::Event::MouseWheelScrolled){
        // std::cout << "croll" << std::endl;
        // this->getGraphic()->getGraphicHelp()->setScroll(true);
        if (this->getEvent().mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
            //avant de move je vérifie si ca dépasse
            float viewTop = this->getGraphic()->getGraphicHelp()->getView().getCenter().y
                - this->getGraphic()->getGraphicHelp()->getView().getSize().y / 2;
            float viewBottom = this->getGraphic()->getGraphicHelp()->getView().getCenter().y
                + this->getGraphic()->getGraphicHelp()->getView().getSize().y / 2;
            float spriteTop = this->getGraphic()->getGraphicHelp()->getSprite().getGlobalBounds().top;
            float spriteBottom = spriteTop + this->getGraphic()->getGraphicHelp()->getSprite().getGlobalBounds().height;
            if (viewTop + this->getEvent().mouseWheelScroll.delta <= spriteTop ||
                viewBottom + this->getEvent().mouseWheelScroll.delta <= spriteBottom){
                    this->getGraphic()->getGraphicHelp()->getView().move
                    (0, this->getEvent().mouseWheelScroll.delta * 26.f);
                }
            this->getGraphic()->getWindow().setView(
                this->getGraphic()->getGraphicHelp()->getView());
            // this->_graphic->getWindow().draw(this->_sprite);
            }
    }
}

void Game::checkButtonMenuPressed(void){
    sf::Vector2i mousePos = sf::Mouse::getPosition(this->getGraphic()->getWindow());
    if (this->getGraphic()->getGraphicMenu()->getButtonHelp().getGlobalBounds().contains(mousePos.x, mousePos.y)){
        this->setStatus(HELP);
        this->getGraphic()->getGraphicHelp()->drawWindowHelp();
    }
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
        return (this->getGraphic()->getGraphicMenu()->setAnimation(false));
    }
    return (this->getGraphic()->getGraphicMenu()->setAnimation(true));
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

