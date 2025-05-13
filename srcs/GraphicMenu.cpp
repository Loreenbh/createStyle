#include "Graphic.hpp"

//*********************************CONSTRUCTOR*********************************
FadeEffect::FadeEffect(bool s, bool f, float fd, float wd, float op, sf::Clock c)
: _stopFade(s), _fade(f), _fadeDuration(fd), _waitDuration(wd), _currOpacity(op), _clock(c) {};

HelpButton::HelpButton(sf::Texture t, sf::Sprite s, sf::Text txt, sf::Font f, float x, 
    float y, float w, float h)
: _buttonHelpT(t), _buttonHelpS(s), _buttonTxt(txt), _buttonFont(f), 
    _refPosX(x), _refPosY(y), _refWidth(w), _refHeigth(h) {};


GraphicMenu::GraphicMenu(Graphic *graphic) : 
_graphic(graphic),
_fadeEffect(false, false, 2.0f, 5.0f, 0.f, sf::Clock()),
_helpButton(sf::Texture(), sf::Sprite(), sf::Text(), sf::Font(), 127, 78, 116, 22),
_currentSpriteIndex(0),
_currentSprite(),
_nextSprite()
{
    _pathSceneMenu.push_back("../scenes/sceneMenu/scene0.png");
    _pathSceneMenu.push_back("../scenes/sceneMenu/scene1.png");
    _pathSceneMenu.push_back("../scenes/sceneMenu/scene2.png");
    _pathSceneMenu.push_back("../scenes/sceneMenu/scene3.png");
    std::cout << "GraphicMenu created" << std::endl;
}

GraphicMenu::~GraphicMenu(){
    std::cout << "GraphicMenu destroyed" << std::endl;
}


//*********************************PUBLIC METHODS*********************************

void   GraphicMenu::createButton(void){
    if (!this->_helpButton._buttonHelpT.loadFromFile("../scenes/sceneMenu/buttonHelp.png"))
        throw std::runtime_error("GraphicMenu: The texture has not been loaded");
        this->_helpButton._buttonHelpS.setTexture(this->_helpButton._buttonHelpT);
    
    sf::Vector2u windowSize = this->_graphic->getWindow().getSize();
    float scaleX = static_cast<float>(windowSize.x) / this->_graphic->getRefWinWidth();
    float scaleY = static_cast<float>(windowSize.y) / this->_graphic->getRefWinHeight();

    //Calculer la pos
    float buttonPosX;
    float buttonPosY;
    buttonPosX = this->_helpButton._refPosX * scaleX;
    buttonPosY = this->_helpButton._refPosY * scaleY;
    
    //Calculer la taille
    float buttonWidth = this->_helpButton._refWidth * scaleX;
    float buttonHeight = this->_helpButton._refHeigth * scaleY;
    
    //Appliquer la nouvelle pos
    this->_helpButton._buttonHelpS.setPosition(buttonPosX, buttonPosY);
    this->_helpButton._buttonHelpS.setScale(scaleX, scaleY);

    if (!this->_helpButton._buttonFont.loadFromFile("../fonts/Napzer.otf"))
        throw std::runtime_error("Erreur : impossible de charger la police Napzer.otf");
    float textScale = (scaleX + scaleY) / 2.0f;
    int scaledFontSize = static_cast<int>(20.0f * textScale);

    this->_helpButton._buttonTxt.setFont(this->_helpButton._buttonFont);
    this->_helpButton._buttonTxt.setString("help");
    this->_helpButton._buttonTxt.setCharacterSize(scaledFontSize);
    this->_helpButton._buttonTxt.setFillColor(sf::Color::Black);
    this->_helpButton._buttonTxt.setPosition(buttonPosX + 7, buttonPosY - 3);
}


void GraphicMenu::loadSceneMenu(void){
    if (this->_pathSceneMenu.size() == 0)
        throw std::runtime_error("The menu doesn't contain any textures");    
    if (this->_pathSceneMenu.size() < 2)
        throw std::runtime_error("The menu must contain at least two textures");    
    for (int i = 0; i < this->_pathSceneMenu.size(); ++i){
        sf::Texture texture;
        if (!texture.loadFromFile(this->_pathSceneMenu[i]))
            throw std::runtime_error("GraphicMenu: The texture has not been loaded");
        this->_textureMenu.push_back(std::move(texture)); 
    }
    //juste set la premiere texture
    this->_currentSprite.setTexture(this->_textureMenu[this->_currentSpriteIndex]);
    this->_graphic->adaptHeightToWin(this->_textureMenu[this->_currentSpriteIndex], this->_currentSprite);

    this->_nextSprite.setTexture(this->_textureMenu[(this->_currentSpriteIndex + 1) % this->_textureMenu.size()]);
    this->_nextSprite.setColor(sf::Color(255, 255, 255, 0));
    this->_graphic->adaptHeightToWin(this->_textureMenu[this->_currentSpriteIndex + 1], this->_nextSprite);
    this->createButton();
}

void GraphicMenu::drawWindowMenu(void) {
    if (this->_fadeEffect._fade) {
        this->_graphic->getWindow().draw(this->_nextSprite);
        this->_graphic->getWindow().draw(this->_currentSprite);
    } 
    else
        this->_graphic->getWindow().draw(this->_currentSprite);
}


void GraphicMenu::getReadyNext(void) {
    int next = (this->_currentSpriteIndex + 1) % this->_textureMenu.size();
    this->_nextSprite.setTexture(this->_textureMenu[next]);
    this->_nextSprite.setColor(sf::Color(255, 255, 255, 0));
    this->_graphic->adaptHeightToWin(this->_textureMenu[next], this->_nextSprite);
}

void GraphicMenu::animationSlideMenu(void) {
    if (!this->_fadeEffect._fade) {
        this->getReadyNext();
        this->_fadeEffect._fade = true;
        this->_fadeEffect._clock.restart();
    }
    if (this->_fadeEffect._fade) {
        float fadeProgress = this->_fadeEffect._clock.getElapsedTime().asSeconds() / this->_fadeEffect._fadeDuration;
        if (fadeProgress <= 1.0f)
        this->_fadeEffect._currOpacity = fadeProgress * 255;
        else
            this->_fadeEffect._currOpacity = 255;

        sf::Color nextColor = this->_nextSprite.getColor();
        nextColor.a = static_cast<sf::Uint8>(this->_fadeEffect._currOpacity);
        this->_nextSprite.setColor(nextColor);

        sf::Color currentColor = this->_currentSprite.getColor();
        currentColor.a = static_cast<sf::Uint8>(255 - this->_fadeEffect._currOpacity);
        this->_currentSprite.setColor(currentColor);

        if (this->_fadeEffect._currOpacity >= 255) {
            if (this->_fadeEffect._clock.getElapsedTime().asSeconds() > this->_fadeEffect._waitDuration) {
                this->_currentSpriteIndex = (this->_currentSpriteIndex + 1) % this->_textureMenu.size();
                this->_currentSprite.setTexture(this->_textureMenu[this->_currentSpriteIndex]);
                this->_graphic->adaptHeightToWin(this->_textureMenu[this->_currentSpriteIndex], this->_currentSprite);
                this->_currentSprite.setColor(sf::Color(255, 255, 255, 255));
                this->_fadeEffect._fade = false;
                this->_fadeEffect._clock.restart();
            }
        }
    }
}

void GraphicMenu::setSprite(std::string str, sf::Sprite &sprite, sf::Texture &texture){
    if (!texture.loadFromFile(str))
        throw std::runtime_error("GraphicMenu: The texture has not been loaded");
    sprite.setTexture(texture);
}

//*********************************GETTERS*********************************
HelpButton &GraphicMenu::getHelpButton(void){
    return (this->_helpButton);
}

FadeEffect &GraphicMenu::getFadeEffect(void){
    return (this->_fadeEffect);
}

bool &GraphicMenu::getFade(void){
    return (this->_fadeEffect._stopFade);
}

sf::Sprite &GraphicMenu::getCurrentSprite(void){
    return (this->_currentSprite);
}

int &GraphicMenu::getCurrentIndex(void){
    return (this->_currentSpriteIndex);
}

sf::Texture &GraphicMenu::getCurrentTexture(void){
    return (this->_textureMenu[this->_currentSpriteIndex]);
}

sf::Texture &HelpButton::getHelpButtonTexture(void){
    return (this->_buttonHelpT);
}

sf::Sprite &HelpButton::getHelpButtonSprite(void){
    return (this->_buttonHelpS);
}

sf::Text &HelpButton::getHelpButtonTxt(void){
    return (this->_buttonTxt);
}

float HelpButton::getRefPosX(void){
    return (this->_refPosX);
}
float HelpButton::getRefPosY(void){
    return (this->_refPosY);
}
float HelpButton::getRefWidth(void){
    return (this->_refWidth);
}
float HelpButton::getRefHeigth(void){
    return (this->_refHeigth);
}
//*********************************SETTERS*********************************
bool &FadeEffect::setFade(bool value){
    this->_stopFade = value;
    return (this->_stopFade);
}
