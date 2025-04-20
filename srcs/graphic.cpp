#include "graphic.hpp"

// ********************************* Constructor
Graphic::Graphic(int windowWidth, int windowHeight) : 
_window(),
_ratio(2.0f),
_windowWidth(windowWidth),
_windowHeight(windowHeight),
_currentSpriteIndex(0),
_currentSpriteMenu(),
_fade(false),
_waiting(false),
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
std::cout << "Graphic construit avec " << _windowWidth << "x" << _windowHeight << std::endl;
}

Graphic::~Graphic(){
    std::cout << "L'objet Graphic a été détruit" << std::endl;
}

// ********************************** Public Methods


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


int Graphic::loadBackgroundMenu(){
    if (this->_pathBackgroundMenu.size() == 0)
        throw std::runtime_error("Aucune texture n'existe!");    
    for (int i = 0; i < this->_pathBackgroundMenu.size(); ++i){
        sf::Texture texture;
        if (!texture.loadFromFile(this->_pathBackgroundMenu[i]))
            throw std::runtime_error("Texture n'est pas chargée");
        //ajouter dans un tableau de vector qui contient des sf::Texture
        this->_textureMenu.push_back(std::move(texture)); 
    }
    // Définir la première texture comme fond
    this->_currentSpriteMenu.setTexture(this->_textureMenu[this->_currentSpriteIndex]);
    this->adaptHeightToWin(this->_textureMenu[this->_currentSpriteIndex], this->_currentSpriteMenu);
    std::cout << "Les images ont été chargées, le tab contient" << this->_pathBackgroundMenu.size() << std::endl;
    return (1);
}


bool Graphic::isWindowOpen() {
    return (this->_window.isOpen());
}

void    Graphic::clearWindow(){
    (this->_window).clear();
}

void    Graphic::displayWindow(){
    this->_window.display();
}

void Graphic::drawWindowMenu() {
    // Pendant le fondu, on dessine les deux
    if (this->_fade) {
        this->_window.draw(this->_currentSpriteMenu); // celle qui s'efface
        this->_window.draw(this->_nextSprite);        // celle qui apparaît
    } 
    else {
        // Sinon on dessine juste la sprite actuelle
        this->_window.draw(this->_currentSpriteMenu);
    }
}

void Graphic::getReadyNext() {
    int next = (this->_currentSpriteIndex + 1) % this->_textureMenu.size();
    this->_nextSprite.setTexture(this->_textureMenu[next]);
    this->_nextSprite.setColor(sf::Color(255, 255, 255, 0)); // Elle commence avec une opacité à 0 (invisible)
    this->adaptHeightToWin(this->_textureMenu[next], this->_nextSprite);
}

//seulement si j'ai 2 images ou plus
void Graphic::animationSlideMenu() {
    // Si fondu pas encore activé
    if (!this->_fade & !this->_waiting) {
        // Déclencher le fondu au moment où on commence l'animation
        this->_currentSpriteMenu.setColor(sf::Color(255, 255, 255, 255));
        this->getReadyNext();
        this->_fade = true;  // On passe à l'état de fondu
        this->_clock.restart();  // Redémarre le chronomètre pour le fondu
    }

 // Si le fondu est activé (on commence à augmenter l'opacité)
 if (this->_fade) {
    // Calculer l'opacité en fonction du temps écoulé
    float fadeProgress = _clock.getElapsedTime().asSeconds() / _fadeDuration;
    // Si la progression est entre 0 et 1, on peut augmenter l'opacité
    if (fadeProgress <= 1.0f)
        this->_currOpacity = fadeProgress * 255;  // Opacité entre 0 et 255
    else
        this->_currOpacity = 255;  // Une fois le fondu terminé, opacité = 255
    // Appliquer l'opacité à l'image suivante
    sf::Color nextColor = this->_nextSprite.getColor();
    nextColor.a = static_cast<sf::Uint8>(this->_currOpacity);  // Mise à jour de l'opacité de la prochaine image
    this->_nextSprite.setColor(nextColor);

    // Appliquer l'opacité à l'image actuelle (elle doit diminuer progressivement)
    sf::Color currentColor = this->_currentSpriteMenu.getColor();
    currentColor.a = static_cast<sf::Uint8>(255 - this->_currOpacity);  // L'opacité de l'image actuelle diminue
    this->_currentSpriteMenu.setColor(currentColor);

    if (this->_currOpacity >= 255) {
        if (!this->_waiting) {
            this->_waiting = true;
            this->_clock.restart(); // commencer la pause
        } else if (this->_clock.getElapsedTime().asSeconds() > this->_waitDuration) {
            // Une fois la pause terminée, on passe à l’image suivante
            this->_currentSpriteIndex = (this->_currentSpriteIndex + 1) % this->_textureMenu.size();
            this->_currentSpriteMenu.setTexture(this->_textureMenu[this->_currentSpriteIndex]);
    
            this->_fade = false;     // on est prêt pour le prochain fondu
            this->_waiting = false;  // réinitialiser la pause
            this->_clock.restart();  // redémarre pour le prochain cycle
        }
    }
}
}


//*******************************    Getters
const sf::RenderWindow& Graphic::getWindow() const{
    return (this->_window);
}

sf::Sprite& Graphic::getSlideMenu(){
    return (this->_currentSpriteMenu);
}

bool &Graphic::getTurn(){
    return (this->_fade);
}