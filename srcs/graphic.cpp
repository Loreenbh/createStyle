#include "graphic.hpp"

// ********************************* Constructor
Graphic::Graphic(int windowWidth, int windowHeight) :
_window(),
_ratio(2.0f),
_windowWidth(windowWidth),
_windowHeight(windowHeight),
_windowRefWidth(900),
_windowRefHeight(600),
_graphicMenu(nullptr)
{
}

Graphic::~Graphic(){
    std::cout << "L'objet GraphicMenu a été détruit" << std::endl;
}

// ********************************** Public Methods

void Graphic::initGraphicMenu(){
    try{
        this->_graphicMenu = new GraphicMenu(this); 
        this->_graphicMenu->loadBackgroundMenu();
    }
    catch(std::exception &e){
        std::cerr << "Erreur dans Graphic: " << e.what() << std::endl;
        throw;
    }
}

void Graphic::adjustWinSize() {
    unsigned int height = this->_windowHeight;
    unsigned int width = this->_windowWidth;

    // On vérifie que la largeur et la hauteur respectent les contraintes minimales
    if (height < 300)
        height = 300;
    if (width < 500)
        width = 500;

    // Maintenir le ratio largeur = 2 * hauteur (ou 1.5 * hauteur pour le ratio 1.5)
    float ratio = 1.5;  // Ici, tu peux mettre n'importe quel facteur (1.5, 2, etc.)
    unsigned int newWidth = static_cast<unsigned int>(height * ratio);

    // Ajuster si la largeur est plus petite que la taille calculée
    if (width < newWidth) {
        this->_windowWidth = newWidth;
        this->_windowHeight = height;
    } else {
        this->_windowHeight = static_cast<unsigned int>(width / ratio);
        this->_windowWidth = width;
    }

    // Limiter la taille à la résolution de l'écran de l'utilisateur
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int maxWidth = desktopMode.width;
    unsigned int maxHeight = desktopMode.height;

    // Ne pas dépasser la taille de l'écran
    if (this->_windowWidth > maxWidth) {
        this->_windowWidth = maxWidth;
        this->_windowHeight = static_cast<unsigned int>(maxWidth / ratio);
    }
    if (this->_windowHeight > maxHeight) {
        this->_windowHeight = maxHeight;
        this->_windowWidth = static_cast<unsigned int>(maxHeight * ratio);
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

    // Récupérer la taille de la texture (texture.getSize() renvoie un sf::Vector2u)
    sf::Vector2u textureSize = texture.getSize();
    float textureHeight = static_cast<float>(textureSize.y); // Conversion en float
    float textureWidth = static_cast<float>(textureSize.x);  // Récupérer la largeur de l'image

    // Calculer le facteur de mise à l'échelle pour la hauteur
    float scaleY = windowHeight / textureHeight;

    // Appliquer le redimensionnement du sprite en fonction de la hauteur
    sprite.setScale(sf::Vector2f(scaleY, scaleY));

    // Vérifier si l'image est plus large que la fenêtre
    float scaledWidth = textureWidth * scaleY; // Calculer la largeur redimensionnée
    if (scaledWidth > windowWidth) {
        // Si l'image est trop large, ajuster l'échelle pour qu'elle tienne dans la fenêtre
        float scaleX = windowWidth / scaledWidth; // Calculer l'échelle en X
        sprite.setScale(sf::Vector2f(scaleX, scaleY)); // Appliquer le redimensionnement en X
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
    this->_graphicMenu->animationSlideMenu();
    this->_graphicMenu->drawWindowMenu();
    this->displayWindow();
}

// ********************************* Getters
sf::RenderWindow &Graphic::getWindow(){
    return (this->_window);
}

float &Graphic::getRefWinWidth(){
    return (this->_windowRefWidth);
}

float &Graphic::getRefWinHeight(){
    return (this->_windowRefHeight);
}