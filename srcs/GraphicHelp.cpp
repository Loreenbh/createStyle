#include "Graphic.hpp"

//*****************************************************************CONSTRUCTOR
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


//*****************************************************************PUBLIC METHODS
void GraphicHelp::loadSceneHelp(){
    sf::Texture texture;
    if (!texture.loadFromFile("../scenes/sceneHelp/test.png"))
            throw std::runtime_error("GraphicHelp: The texture has not been loaded");
    this->_sprite.setTexture(texture);
    // this->_view(sf::FloatRect(0, 0, this->_graphic->getWidthWin(), this->_graphic->getHeigthWin()));
    // this->_graphic->adaptHeightToWin(texture, this->_sprite);
    // this->_buttonPlay.setButtonMenu();
    // this->_buttonHelp.setButtonMenu();

    //verifier l existance de l image
    //charger la texture
    //set la texture
}


void GraphicHelp::drawWindowHelp() {
    this->_graphic->getWindow().draw(this->_sprite);
    this->_graphic->displayWindow();
}


//*****************************************************************GETTERS
sf::View &GraphicHelp::getView(){
    return (this->_view);
}

sf::Sprite &GraphicHelp::getSprite(){
    return (this->_sprite);
}
