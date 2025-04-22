#include "Button.hpp"
#include "graphic.hpp"

// ********************************* Constructor
Button::Button(std::string txt, Graphic *graphic, int n):
_graphic(graphic),
_id(n),
_str(txt),
_buttonRefWidth(116),
_buttonRefHeight(22),
_helpRefX(127),
_helpRefY(78),
_playRefX(240),
_playRefY(308)
{
}

Button::~Button(){
}

// ********************************** Public Methods
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
    if (!this->_font.loadFromFile("../fonts/AMORIA.otf"))
    throw std::runtime_error("Erreur : impossible de charger la police AMORIA.otf");
    this->_text.setFont(this->_font);
    this->_text.setString(this->_str);
    this->_text.setFillColor(sf::Color::Black);
    this->_text.setPosition(buttonPosX, buttonPosY);
}

// ********************************* Getters
sf::Text &Button::getText(){
    return (this->_text);
}