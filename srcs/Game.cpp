#include "Game.hpp"

//*********************************CONSTRUCTOR*********************************
Game::Game() : 
    _event(), _state(MENU), _graphics(nullptr), _helpButtonPressed(false){
    try{
        _graphics = new Graphic(10, 10); //rien a verifier
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

//*********************************PUBLIC METHODS*********************************

void Game::selectEventMenu(void){
    this->hoverButtonsMenu(); //met a jour booleen animation
    sf::Vector2i mousePos = sf::Mouse::getPosition(this->getGraphic()->getWindow());
    if (this->getEvent().type == sf::Event::MouseButtonPressed && this->getEvent().mouseButton.button == sf::Mouse::Left){
        if (this->getGraphic()->getGraphicMenu()->getHelpButton().getGlobalBounds().contains(mousePos.x, mousePos.y)){
            this->getGraphic()->getGraphicMenu()->setSprite("../scenes/sceneMenu/buttonHelpClic.png", 
                this->getGraphic()->getGraphicMenu()->getHelpButton(), this->getGraphic()->getGraphicMenu()->getHelpButtonTexture());
            this->_helpButtonPressed = true;
        }
    }

    if (this->getEvent().type == sf::Event::MouseButtonReleased && this->getEvent().mouseButton.button == sf::Mouse::Left){
        if (this->_helpButtonPressed &&
            this->getGraphic()->getGraphicMenu()->getHelpButton().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            this->setStatus(HELP);
            this->getGraphic()->getGraphicHelp()->getBlur() = true;
            this->_helpButtonPressed = false;
        }
    }
}

void Game::selectEventHelp(void){
    if (this->getEvent().type == sf::Event::KeyPressed && 
        this->getEvent().key.code == sf::Keyboard::Enter && this->_graphics->getGraphicHelp()->getSpriteDisplayed()){
        this->getGraphic()->getGraphicHelp()->getPressEnter() = true;
    }
}

bool Game::hoverButtonsMenu(void){
    sf::Vector2i mousePos = sf::Mouse::getPosition(this->_graphics->getWindow());
    if (this->getGraphic()->getGraphicMenu()->getHelpButton().getGlobalBounds().contains(mousePos.x, mousePos.y)){
        this->getGraphic()->getGraphicMenu()->setSprite("../scenes/sceneMenu/buttonHelpHover.png", 
            this->getGraphic()->getGraphicMenu()->getHelpButton(), this->getGraphic()->getGraphicMenu()->getHelpButtonTexture());
        }else{
        this->getGraphic()->getGraphicMenu()->setSprite("../scenes/sceneMenu/buttonHelp.png", 
            this->getGraphic()->getGraphicMenu()->getHelpButton(), this->getGraphic()->getGraphicMenu()->getHelpButtonTexture());
        return (this->getGraphic()->getGraphicMenu()->setFade(false));
    }
    return (this->getGraphic()->getGraphicMenu()->setFade(true));
}


void Game::closeWindow(void){
    this->_graphics->getWindow().close();
}

//*********************************GETTERS*********************************
Graphic *Game::getGraphic(void) const{
    return (this->_graphics);
}

GameState &Game::getStatus(void){
    return (this->_state);
}

sf::Event &Game::getEvent(void){
    return (this->_event);
}

//*********************************SETTERS*********************************
GameState &Game::setStatus(GameState status){
    this->_state = status;
    return (this->_state);
}

