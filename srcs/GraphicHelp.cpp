#include "Graphic.hpp"

//*********************************CONSTRUCTORS*********************************
GraphicHelp::GraphicHelp(Graphic *graphic) : 
_buttonReturn("Back", graphic, 3),
_graphic(graphic),
_view(sf::FloatRect(0, 0, this->_graphic->getWidthWin(), this->_graphic->getHeigthWin()))
{
    std::cout << "GraphicHelp created" << std::endl;
}

GraphicHelp::~GraphicHelp(){
    std::cout << "GraphicHelp destroyed" << std::endl;
}


//*********************************PUBLIC METHODS*********************************
void GraphicHelp::loadSceneHelp(void){
    if (!this->_texture.loadFromFile("../scenes/sceneHelp/test.png"))
            throw std::runtime_error("GraphicHelp: The texture has not been loaded");
    this->_sprite.setTexture(this->_texture);
}


void GraphicHelp::drawWindowHelp(void) {
    this->_graphic->getWindow().clear();
    this->_graphic->getWindow().draw(this->_sprite);
    this->_graphic->displayWindow();
}


//*********************************GETTERS*********************************
sf::View &GraphicHelp::getView(void){
    return (this->_view);
}

sf::Sprite &GraphicHelp::getSprite(void){
    return (this->_sprite);
}

//*********************************SETTERS*********************************