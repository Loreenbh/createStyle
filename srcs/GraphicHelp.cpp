#include "Graphic.hpp"

//*****************************************************************CONSTRUCTOR
GraphicHelp::GraphicHelp(Graphic *graphic) : 
_buttonReturn("Back", graphic, 3),
_graphic(graphic),
_view(sf::FloatRect(0, 0, this->_graphic->getWidthWin(), this->_graphic->getHeigthWin())),
_scroll(false)
{
    std::cout << "GraphicHelp created" << std::endl;
}

GraphicHelp::~GraphicHelp(){
    std::cout << "GraphicHelp destroyed" << std::endl;
}


//*****************************************************************PUBLIC METHODS
void GraphicHelp::loadSceneHelp(){
    if (!this->_texture.loadFromFile("../scenes/sceneHelp/test.png"))
            throw std::runtime_error("GraphicHelp: The texture has not been loaded");
    this->_sprite.setTexture(this->_texture);
}


void GraphicHelp::drawWindowHelp() {
    this->_graphic->getWindow().clear();
    // if (!this->_scroll)
    this->_graphic->getWindow().draw(this->_sprite);
    this->_graphic->displayWindow();
    // this->setScroll(false);
}


//*****************************************************************GETTERS
sf::View &GraphicHelp::getView(){
    return (this->_view);
}

sf::Sprite &GraphicHelp::getSprite(){
    return (this->_sprite);
}

//*****************************************************************SETTERS
bool &GraphicHelp::setScroll(bool value){
    this->_scroll = value;
    return (this->_scroll);
}
