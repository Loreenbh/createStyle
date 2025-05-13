#include "Graphic.hpp"

//*********************************CONSTRUCTOR*********************************
Graphic::Graphic(int windowWidth, int windowHeight) :
_window(),
_ratio(2.0f),
_windowWidth(windowWidth),
_windowHeight(windowHeight),
_winRefWidth(900),
_winRefHeight(600),
_winRefMaxHeight(1080),
_winRefMaxWidth(1920),
_graphicMenu(nullptr),
_graphicHelp(nullptr)
{
}

Graphic::~Graphic(){
    std::cout << "Graphic destroyed" << std::endl;
    if (this->_graphicMenu)
        delete this->_graphicMenu;
    if (this->_graphicHelp)
        delete this->_graphicHelp;
}

//*********************************PUBLIC METHODS*********************************
void Graphic::initGraphicMenu(void){
    try{
        this->_graphicMenu = new GraphicMenu(this); 
        this->_graphicMenu->loadSceneMenu();
    }
    catch(std::exception &e){
        throw;
    }
    std::cout << "GraphicMenu created" << std::endl;
}

void Graphic::initGraphicHelp(void){
    try{
        this->_graphicHelp = new GraphicHelp(this, this->getGraphicMenu()); 
        this->_graphicHelp->loadSceneHelp();
    }
    catch(std::exception &e){
        throw;
    }
    std::cout << "GraphicHelp created" << std::endl;
}

void Graphic::adjustWinSize(void) {
    unsigned int height = this->_windowHeight;
    unsigned int width = this->_windowWidth;

    if (height < 300)
        height = 300;
    if (width < 500)
        width = 500;

    // Maintenir le ratio largeur = 2 * hauteur (ou 1.5 * hauteur pour le ratio 1.5)
    float ratio = 1.5;  // Ici, tu peux mettre n'importe quel facteur (1.5, 2, etc.)
    unsigned int newWidth = static_cast<unsigned int>(height * ratio);

    if (width < newWidth) {
        this->_windowWidth = newWidth;
        this->_windowHeight = height;
    } else {
        this->_windowHeight = static_cast<unsigned int>(width / ratio);
        this->_windowWidth = width;
    }
    if (this->_windowWidth > this->_winRefMaxWidth) {
        this->_windowWidth = this->_winRefMaxWidth;
        this->_windowHeight = static_cast<unsigned int>(this->_winRefMaxWidth / ratio);
    }
    if (this->_windowHeight > this->_winRefMaxHeight) {
        this->_windowHeight = this->_winRefMaxHeight;
        this->_windowWidth = static_cast<unsigned int>(this->_winRefMaxHeight * ratio);
    }
}


void Graphic::createWindow(void){
    this->adjustWinSize();
    this->_window.create(sf::VideoMode(this->_windowWidth, this->_windowHeight), "Mon Jeu");
    if (!this->_window.isOpen()) 
        throw std::runtime_error("Impossible de créer la fenêtre !");
    this->_window.setFramerateLimit(60);
}

void    Graphic::adaptHeightToWin(sf::Texture &texture, sf::Sprite &sprite){
    float windowHeight = this->_window.getSize().y;
    float windowWidth = this->_window.getSize().x;

    sf::Vector2u textureSize = texture.getSize();
    float textureHeight = static_cast<float>(textureSize.y);
    float textureWidth = static_cast<float>(textureSize.x);

    // Calculer le facteur de mise à l'échelle pour la hauteur
    float scaleY = windowHeight / textureHeight;

    // Appliquer le redimensionnement du sprite en fonction de la hauteur
    sprite.setScale(sf::Vector2f(scaleY, scaleY));

    // Vérifier si l'image est plus large que la fenêtre
    float scaledWidth = textureWidth * scaleY;
    if (scaledWidth > windowWidth) {
        float scaleX = windowWidth / scaledWidth;
        sprite.setScale(sf::Vector2f(scaleX, scaleY));
    }
}

bool Graphic::isWindowOpen(void) {
    return (this->_window.isOpen());
}

void    Graphic::clearWindow(void){
    this->_window.clear();
}

void    Graphic::displayWindow(void){
    this->_window.display();
}

void Graphic::handleMenuAnimation(void) {
    this->clearWindow();
    if (!this->getGraphicMenu()->getFade()){
        this->_graphicMenu->animationSlideMenu();
        this->_graphicMenu->drawWindowMenu();
    }
    else{
        this->_graphicMenu->getCurrentSprite().setTexture(
            this->getGraphicMenu()->getCurrentTexture());
        this->getGraphicMenu()->getCurrentSprite().setColor(sf::Color(255, 255, 255, 255));
    }
    this->getWindow().draw(this->getGraphicMenu()->getCurrentSprite());
    this->getWindow().draw(this->getGraphicMenu()->getHelpButton().getHelpButtonSprite());
    this->getWindow().draw(this->getGraphicMenu()->getHelpButton().getHelpButtonTxt());
    this->displayWindow(); 
}

void Graphic::handleHelpAnimation(void){
    if (!this->getGraphicHelp()->getEndBlur())
        this->getGraphicHelp()->applyBlur();
    else{
        if (this->getGraphicHelp()->getPressEnter()){ //tant que animation pas fini tu rentrres pas
            if (this->getGraphicHelp()->getSpriteDisplayed() && 
                this->getGraphicHelp()->getCurrentSpriteIndex() + 1 < this->getGraphicHelp()->getRulesGame().size()){
                this->getGraphicHelp()->getPressEnter() = false;
                this->getGraphicHelp()->getSpriteDisplayed() = false;
                this->getGraphicHelp()->getCurrentSpriteIndex() += 1;
                this->getGraphicHelp()->getCurrentSprite().setTexture
                (this->_graphicHelp->getRulesGame()[this->getGraphicHelp()->getCurrentSpriteIndex()].first);
                this->adaptHeightToWin(this->getGraphicHelp()->getRulesGame()[this->getGraphicHelp()->getCurrentSpriteIndex()].first, 
                    this->getGraphicHelp()->getCurrentSprite());
                this->getGraphicHelp()->getElapsedTime() = 0.0f;
                this->getGraphicHelp()->getBlurProgress() = 0.0f;
            }
        }
        this->clearWindow();
        this->getGraphicHelp()->drawBlurBackground();
        // this->getGraphicHelp()->ruleAnimation(this->getGraphicHelp()->getCurrentSpriteIndex(), 
        //     ,this->getGraphicHelp()->getBlurProgress());
        this->getGraphicHelp()->ruleAnimation(this->getGraphicHelp()->getCurrentSpriteIndex(), 
        this->getGraphicHelp()->getRulesGame()[this->getGraphicHelp()->getCurrentSpriteIndex()].second ,this->getGraphicHelp()->getBlurProgress());
        std::vector<sf::Sprite>::iterator it = this->getGraphicHelp()->getDisplayedSprites().begin();
        for (it ; it != this->getGraphicHelp()->getDisplayedSprites().end() ; ++it){
            this->_window.draw(*it);
        }
        //dessiner les anciens sprites sauvegardés;
        this->_window.draw(this->getGraphicHelp()->getCurrentSprite());
        //ajouter seulement si existe pas
        if (this->getGraphicHelp()->getSpriteDisplayed() && this->getGraphicHelp()->getCurrentSpriteIndex() == static_cast<int>(this->getGraphicHelp()->getDisplayedSprites().size())) {
            std::cout << "sprite[" << this->getGraphicHelp()->getCurrentSpriteIndex() << "] est ajouté" << std::endl;
            this->getGraphicHelp()->getDisplayedSprites().push_back(this->getGraphicHelp()->getCurrentSprite());
        }
        this->displayWindow();
    }
}

//*********************************GETTERS*********************************
sf::RenderWindow &Graphic::getWindow(void){
    return (this->_window);
}

float &Graphic::getRefWinWidth(void){
    return (this->_winRefWidth);
}

float &Graphic::getRefWinHeight(void){
    return (this->_winRefHeight);
}

float &Graphic::getWidthWin(void) {
    return (this->_windowWidth);
}

float &Graphic::getHeigthWin(void) {
    return (this->_windowHeight);
}

GraphicMenu  *Graphic::getGraphicMenu(void){
    return (this->_graphicMenu);
}

GraphicHelp  *Graphic::getGraphicHelp(void){
    return (this->_graphicHelp);
}