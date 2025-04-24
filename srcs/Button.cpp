#include "Button.hpp"
#include "Graphic.hpp"

//*****************************************************************CONSTRUCTOR
Button::Button(std::string txt, Graphic *graphic, int n):
_graphic(graphic),
_id(n),
_buttonRefWidth(116),
_buttonRefHeight(22),
_helpRefX(127),
_helpRefY(78),
_playRefX(240),
_playRefY(308)
{
    _atrButton._str = txt;
    std::cout << "Button created" << std::endl;
}

Button::~Button(){
    std::cout << "Button destroyed" << std::endl;

}

//*****************************************************************PUBLIC METHODS
void    Button::setButtonMenu(){
    sf::Vector2u windowSize = this->_graphic->getWindow().getSize();
    float scaleX = static_cast<float>(windowSize.x) / this->_graphic->getRefWinWidth();
    float scaleY = static_cast<float>(windowSize.y) / this->_graphic->getRefWinHeight();

    //Calculer la pos
    float buttonPosX;
    float buttonPosY;
    if (this->_id == 0){
        buttonPosX = this->_helpRefX * scaleX;
        buttonPosY = this->_helpRefY * scaleY;
    }
    else{
        buttonPosX = this->_playRefX * scaleX;
        buttonPosY = this->_playRefY * scaleY;
    }
    //Calculer la taille
    float buttonWidth = this->_buttonRefWidth * scaleX;
    float buttonHeight = this->_buttonRefHeight * scaleY;

    //Appliquer la nouvelle pos
    this->setPosition(buttonPosX, buttonPosY);
    this->setSize(sf::Vector2f(buttonWidth, buttonHeight));
    this->setFillColor(sf::Color::White);
    if (!this->_atrButton._font.loadFromFile("../fonts/Napzer.otf"))
        throw std::runtime_error("Erreur : impossible de charger la police Napzer.otf");
    this->_atrButton._text.setFont(this->_atrButton._font);
    this->_atrButton._text.setCharacterSize(20);
    this->_atrButton._text.setScale(scaleX, scaleY);
    this->_atrButton._text.setString(this->_atrButton._str);
    this->_atrButton._text.setFillColor(sf::Color::Black);
    this->_atrButton._text.setPosition(buttonPosX + 7, buttonPosY - 3);
}

//*****************************************************************GETTERS
sf::Text &Button::getText(){
    return (this->_atrButton._text);
}