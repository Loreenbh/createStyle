#include "Graphic.hpp"

//*****************************************************************CONSTRUCTOR
GraphicMenu::GraphicMenu(Graphic *graphic) : 
_graphic(graphic),
_currentSpriteIndex(0),
_currentSpriteMenu(),
_stopAnimation(false),
_fade(false),
_fadeDuration(2.f),
_waitDuration(5.f),
_currOpacity(0.f),
_clock(),
_nextSprite(),
_buttonHelp("help", graphic, 0),
_buttonPlay("play", graphic, 1)
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


//*****************************************************************PUBLIC METHODS
void GraphicMenu::loadSceneMenu(){
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
    this->_currentSpriteMenu.setTexture(this->_textureMenu[this->_currentSpriteIndex]);
    this->_graphic->adaptHeightToWin(this->_textureMenu[this->_currentSpriteIndex], this->_currentSpriteMenu);

    this->_nextSprite.setTexture(this->_textureMenu[(this->_currentSpriteIndex + 1) % this->_textureMenu.size()]);
    this->_nextSprite.setColor(sf::Color(255, 255, 255, 0));
    this->_graphic->adaptHeightToWin(this->_textureMenu[this->_currentSpriteIndex + 1], this->_nextSprite);
    this->_buttonPlay.setButtonMenu();
    this->_buttonHelp.setButtonMenu();
}

void GraphicMenu::drawWindowMenu() {
    if (this->_fade) {
        this->_graphic->getWindow().draw(this->_nextSprite);
        this->_graphic->getWindow().draw(this->_currentSpriteMenu);
    } 
    else
        this->_graphic->getWindow().draw(this->_currentSpriteMenu);
    this->_graphic->getWindow().draw(this->_buttonPlay);
    this->_graphic->getWindow().draw(this->_buttonPlay.getText());
    this->_graphic->getWindow().draw(this->_buttonHelp);
    this->_graphic->getWindow().draw(this->_buttonHelp.getText());
}


void GraphicMenu::getReadyNext() {
    int next = (this->_currentSpriteIndex + 1) % this->_textureMenu.size();
    this->_nextSprite.setTexture(this->_textureMenu[next]);
    this->_nextSprite.setColor(sf::Color(255, 255, 255, 0));
    this->_graphic->adaptHeightToWin(this->_textureMenu[next], this->_nextSprite);
}

void GraphicMenu::animationSlideMenu() {
    if (!this->_fade) {
        this->getReadyNext();
        this->_fade = true;
        this->_clock.restart();
    }
    if (this->_fade) {
        // Calculer l'opacité en fonction du temps écoulé
        float fadeProgress = this->_clock.getElapsedTime().asSeconds() / _fadeDuration;
        if (fadeProgress <= 1.0f)
            this->_currOpacity = fadeProgress * 255;
        else
            this->_currOpacity = 255;  // Une fois le fondu terminé, opacité = 255

        sf::Color nextColor = this->_nextSprite.getColor();
        nextColor.a = static_cast<sf::Uint8>(this->_currOpacity);
        this->_nextSprite.setColor(nextColor);

        sf::Color currentColor = this->_currentSpriteMenu.getColor();
        currentColor.a = static_cast<sf::Uint8>(255 - this->_currOpacity);
        this->_currentSpriteMenu.setColor(currentColor);

        if (this->_currOpacity >= 255) {
            if (this->_clock.getElapsedTime().asSeconds() > this->_waitDuration) {
                this->_currentSpriteIndex = (this->_currentSpriteIndex + 1) % this->_textureMenu.size();
                this->_currentSpriteMenu.setTexture(this->_textureMenu[this->_currentSpriteIndex]);
                this->_graphic->adaptHeightToWin(this->_textureMenu[this->_currentSpriteIndex], this->_currentSpriteMenu);
                this->_currentSpriteMenu.setColor(sf::Color(255, 255, 255, 255));
                this->_fade = false;
                this->_clock.restart();
            }
        }
    }
}

bool GraphicMenu::isAnimated(void) const{
    return (this->_stopAnimation);
}

//*****************************************************************GETTERS
Button &GraphicMenu::getButtonHelp(void){
    return (this->_buttonHelp);
}

Button &GraphicMenu::getButtonPlay(void){
    return (this->_buttonPlay);
}
