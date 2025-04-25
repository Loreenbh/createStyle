#include "Graphic.hpp"

//*****************************************************************CONSTRUCTOR
Graphic::Graphic(int windowWidth, int windowHeight) :
_window(),
_ratio(2.0f),
_windowWidth(windowWidth),
_windowHeight(windowHeight),
_windowRefWidth(900),
_windowRefHeight(600),
_windowRefMaxHeight(1080),
_windowRefMaxWidth(1920),
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


//*****************************************************************PUBLIC METHODS
void Graphic::initGraphicMenu(){
    try{
        this->_graphicMenu = new GraphicMenu(this); 
        this->_graphicMenu->loadSceneMenu();
    }
    catch(std::exception &e){
        throw;
    }
    std::cout << "GraphicMenu created" << std::endl;
}

void Graphic::initGraphicHelp(){
    try{
        this->_graphicHelp = new GraphicHelp(this); 
        this->_graphicHelp->loadSceneHelp();
    }
    catch(std::exception &e){
        throw;
    }
    std::cout << "GraphicHelp created" << std::endl;
}

void Graphic::adjustWinSize() {
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
    if (this->_windowWidth > this->_windowRefMaxWidth) {
        this->_windowWidth = this->_windowRefMaxWidth;
        this->_windowHeight = static_cast<unsigned int>(this->_windowRefMaxWidth / ratio);
    }
    if (this->_windowHeight > this->_windowRefMaxHeight) {
        this->_windowHeight = this->_windowRefMaxHeight;
        this->_windowWidth = static_cast<unsigned int>(this->_windowRefMaxHeight * ratio);
    }
}


void Graphic::createWindow(){
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

bool Graphic::isWindowOpen() {
    return (this->_window.isOpen());
}

void    Graphic::clearWindow(){
    this->_window.clear();
}

void    Graphic::displayWindow(){
    this->_window.display();
}

void Graphic::handleMenuAnimation() {
    this->clearWindow();
    if (!this->getGraphicMenu()->getAnimation()){
        this->_graphicMenu->animationSlideMenu();
        this->_graphicMenu->drawWindowMenu();
    }
    else{
        this->_graphicMenu->getCurrentSprite().setTexture(
            this->getGraphicMenu()->getCurrentTexture());
        this->getGraphicMenu()->getCurrentSprite().setColor(sf::Color(255, 255, 255, 255));
    }
    this->getWindow().draw(this->getGraphicMenu()->getCurrentSprite());
    this->getWindow().draw(this->getGraphicMenu()->getButtonPlay());
    this->getWindow().draw(this->getGraphicMenu()->getButtonPlay().getText());
    this->getWindow().draw(this->getGraphicMenu()->getButtonHelp());
    this->getWindow().draw(this->getGraphicMenu()->getButtonHelp().getText());
    this->displayWindow();
}

void Graphic::handleHelpAnimation(){
    this->clearWindow();
    this->_window.draw(this->getGraphicHelp()->getSprite());
    this->displayWindow();
}

//*****************************************************************GETTERS
sf::RenderWindow &Graphic::getWindow(){
    return (this->_window);
}

float &Graphic::getRefWinWidth(){
    return (this->_windowRefWidth);
}

float &Graphic::getRefWinHeight(){
    return (this->_windowRefHeight);
}

float &Graphic::getWidthWin() {
    return (this->_windowWidth);
}

float &Graphic::getHeigthWin() {
    return (this->_windowHeight);
}

GraphicMenu  *Graphic::getGraphicMenu(){
    return (this->_graphicMenu);
}

GraphicHelp  *Graphic::getGraphicHelp(){
    return (this->_graphicHelp);
}