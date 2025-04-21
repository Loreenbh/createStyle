#include "graphic.hpp"

// ********************************* Constructor
GraphicMenu::GraphicMenu(Graphic *graphic) : 
_graphic(graphic),
_currentSpriteIndex(0),
_currentSpriteMenu(),
_fade(false),
_fadeDuration(2.f),
_waitDuration(5.f),
_currOpacity(0.f),
_clock(),
_nextSprite()
{
    _pathBackgroundMenu.push_back("../backgroundIndex/background0.png");
    _pathBackgroundMenu.push_back("../backgroundIndex/background1.png");
    _pathBackgroundMenu.push_back("../backgroundIndex/background2.png");
    _pathBackgroundMenu.push_back("../backgroundIndex/background3.png");
// std::cout << "Graphic construit avec " << _windowWidth << "x" << _windowHeight << std::endl;
}

GraphicMenu::~GraphicMenu(){
    std::cout << "L'objet Graphic a été détruit" << std::endl;
}

// ********************************** Public Methods
int GraphicMenu::loadBackgroundMenu(){
    if (this->_pathBackgroundMenu.size() == 0)
        throw std::runtime_error("Aucune texture n'existe!");    
    for (int i = 0; i < this->_pathBackgroundMenu.size(); ++i){
        sf::Texture texture;
        if (!texture.loadFromFile(this->_pathBackgroundMenu[i]))
            throw std::runtime_error("Texture n'est pas chargée");
        this->_textureMenu.push_back(std::move(texture)); 
    }
    this->_currentSpriteMenu.setTexture(this->_textureMenu[this->_currentSpriteIndex]);
    this->_graphic->adaptHeightToWin(this->_textureMenu[this->_currentSpriteIndex], this->_currentSpriteMenu);

    this->_nextSprite.setTexture(this->_textureMenu[(this->_currentSpriteIndex + 1) % this->_textureMenu.size()]);
    this->_nextSprite.setColor(sf::Color(255, 255, 255, 0)); // Elle commence avec une opacité à 0 (invisible)
    this->_graphic->adaptHeightToWin(this->_textureMenu[this->_currentSpriteIndex + 1], this->_nextSprite);

    //Charger les boutons
    this->_buttonHelp.setSize(sf::Vector2f(10, 20));
    this->_buttonHelp.setFillColor(sf::Color::Blue);
    this->_buttonHelp.setPosition(100, 200);
    std::cout << "Les images ont été chargées, le tab contient" << this->_pathBackgroundMenu.size() << std::endl;
    return (1);
}

void GraphicMenu::drawWindowMenu() {
    if (this->_fade) {
        this->_graphic->getWindow().draw(this->_nextSprite);
        this->_graphic->getWindow().draw(this->_currentSpriteMenu);
    } 
    else
        this->_graphic->getWindow().draw(this->_currentSpriteMenu);
    this->_graphic->getWindow().draw(this->_buttonHelp);
}


void GraphicMenu::getReadyNext() {
    int next = (this->_currentSpriteIndex + 1) % this->_textureMenu.size();
    this->_nextSprite.setTexture(this->_textureMenu[next]);
    this->_nextSprite.setColor(sf::Color(255, 255, 255, 0));
    this->_graphic->adaptHeightToWin(this->_textureMenu[next], this->_nextSprite);
}

//seulement si j'ai 2 images ou plus
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
                this->_currentSpriteMenu.setColor(sf::Color(255, 255, 255, 255));
                this->_fade = false;
                this->_clock.restart();
            }
        }
    }
}

