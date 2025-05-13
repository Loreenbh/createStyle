#include "Graphic.hpp"

//*********************************CONSTRUCTORS*********************************
SpriteAttributes::SpriteAttributes(): _id(-1), _posStartX(0), _posStartY(0),
  _posEndX(0), _posEndY(0), _sizeStartX(0), _sizeStartY(0), 
  _sizeEndX(0), _sizeEndY(0), _angle(0) {};

SpriteAttributes::SpriteAttributes(int i, float psx, float psy, float pex, float pey,
    float sizeSX, float sizeSY, float sizeEX, float sizeEY, float a)
: _id(i), _posStartX(psx), _posStartY(psy), _posEndX(pex), 
    _posEndY(pey), _sizeStartX(sizeSX), _sizeStartY(sizeSY), _sizeEndX(sizeEX),
    _sizeEndY(sizeEY), _angle(a) {};


GraphicHelp::GraphicHelp(Graphic *graphic, GraphicMenu *GraphicMenu) : 
_graphic(graphic),
_graphicMenu(GraphicMenu),
_view(sf::FloatRect(0, 0, this->_graphic->getWidthWin(), this->_graphic->getHeigthWin())),
_blurIntensity(0.0f),
_blurDuration(1.0f),
_blurActive(false),
_blurProgress(0.0f),
_elapsedTime(0.0f),
_clock(),
_currentSprite(),
_currentSpriteIndex(0),
_refSizeEnd(400),
_spriteDisplayed(false),
_endBlur(false),
_pressEnter(false),
_finalSprite()
{
    _pathRulesGame.push_back("../scenes/sceneHelp/rules01.png");
    _pathRulesGame.push_back("../scenes/sceneHelp/rules02.png");
    _pathRulesGame.push_back("../scenes/sceneHelp/rules03.png");
    _pathRulesGame.push_back("../scenes/sceneHelp/rules04.png");

    std::cout << "GraphicHelp created" << std::endl;
}

GraphicHelp::~GraphicHelp(){
    std::cout << "GraphicHelp destroyed" << std::endl;
}


//*********************************PUBLIC METHODS*********************************
void GraphicHelp::loadSceneHelp(void){
    //Blur
    if (!this->_blur.loadFromFile("../effects/blur.frag", sf::Shader::Fragment)) {
        std::cerr << "Erreur lors du chargement du shader de flou." << std::endl;
        return;
    }

    //Post-it
    if (this->_pathRulesGame.size() == 0)
        throw std::runtime_error("The menu doesn't contain any textures");        
    for (int i = 0; i < this->_pathRulesGame.size(); ++i){
        sf::Texture texture;
        if (!texture.loadFromFile(this->_pathRulesGame[i]))
            throw std::runtime_error("GraphicMenu: The texture has not been loaded");
        // this->_rulesGame.push_back(std::move(texture), SpriteAttributes());
        this->_rulesGame.emplace_back(std::move(texture), SpriteAttributes());

    }
    //je set juste la premiere texture
    this->_currentSprite.setTexture(this->_rulesGame[this->_currentSpriteIndex].first);
    this->_graphic->adaptHeightToWin(this->_rulesGame[this->_currentSpriteIndex].first, this->_currentSprite);
}

void GraphicHelp::getStartPosRule(float &x, float &y, float scaleX, float scaleY){
    if (this->_currentSpriteIndex == 0){
        x = this->getGraphicMenu()->getHelpButton().getRefPosX() * scaleX;
        y = this->getGraphicMenu()->getHelpButton().getRefPosY() * scaleY;
    }
    else if (this->_currentSpriteIndex == 1){  
        x = 100 * scaleX;
        y = 300 * scaleY;
    }
    else if (this->_currentSpriteIndex == 2){  
        x = 100 * scaleX;
        y = 300 * scaleY;
    }
    else if (this->_currentSpriteIndex == 3){  
        x = 100 * scaleX;
        y = 300 * scaleY;
    }
}


void GraphicHelp::getStartSizeRule(float &w, float &h, float scaleX, float scaleY){
    if (this->_currentSpriteIndex == 0){
        w = this->getGraphicMenu()->getHelpButton()._refWidth * scaleX;
        h = this->getGraphicMenu()->getHelpButton()._refHeigth * scaleY;
    }
    else{
        w = this->_refSizeEnd * scaleX * 3;
        h = this->_refSizeEnd * scaleY * 3;
    }
}

void GraphicHelp::getEndSizeRule(float &w, float &h, float scaleX, float scaleY){
    w = this->_refSizeEnd * scaleX;
    h = this->_refSizeEnd * scaleY;
}

void GraphicHelp::chooseRotation(SpriteAttributes &curr){ //&
    if (curr._id == 0){
        curr._angle = 5;
        this->_currentSprite.setRotation(curr._angle);
    }
    else if (curr._id == 1){
        curr._angle = -30;
        this->_currentSprite.setRotation(curr._angle);
    }
    else if (curr._id == 2){
        curr._angle = 20;
        this->_currentSprite.setRotation(curr._angle);
    }
    else if (curr._id == 3){
        curr._angle = -15;
        this->_currentSprite.setRotation(curr._angle);
    }
}

void GraphicHelp::drawBlurBackground(void){
    sf::RenderTexture blurPass;
    int w = this->_graphic->getWidthWin();
    int h = this->_graphic->getHeigthWin();
    blurPass.create(w, h);
    blurPass.clear();
    blurPass.draw(this->getGraphicMenu()->getCurrentSprite());
    blurPass.display();

    // Application du flou isotrope (shader circulaire)
    const float maxBlurRadius = 30.0f;  // Peut être ajusté

    this->_blur.setUniform("texture", blurPass.getTexture());
    this->_blur.setUniform("radius", this->_blurIntensity * maxBlurRadius);

    this->_graphic->getWindow().clear();
    this->_finalSprite.setTexture(blurPass.getTexture());
    this->_graphic->getWindow().draw(this->_finalSprite, &this->_blur);
}

// void GraphicHelp::ruleAnimation(int id, float animationProgress)
void GraphicHelp::ruleAnimation(int id, SpriteAttributes &curr, float animationProgress) {
    if (id >= 1){
        curr._id = id;
        float deltaTime = this->_clock.restart().asSeconds();
        const float maxDeltaTime = 0.1f;
        if (deltaTime > maxDeltaTime)
            deltaTime = maxDeltaTime;
        this->_elapsedTime += deltaTime;
        animationProgress = std::min(this->_elapsedTime / this->_blurDuration, 1.0f);
        if (this->_elapsedTime >= this->_blurDuration && !this->_spriteDisplayed){ //changerblurduration
            this->_spriteDisplayed = true;
        }
    }
    // 2. Taille de la fenêtre
    sf::Vector2u windowSize = this->_graphic->getWindow().getSize();
    float scaleX = static_cast<float>(windowSize.x) / this->_graphic->getRefWinWidth();
    float scaleY = static_cast<float>(windowSize.y) / this->_graphic->getRefWinHeight();
    
    // 3. Position départ (position du bouton au début)
    // float posStartX, posStartY;
    // sf::Vector2f startPos = this->getStartPosRule(posStartX, posStartY, scaleX, scaleY);

    this->getStartPosRule(curr._posStartX, curr._posStartY, scaleX, scaleY);

    // 4. Taille départ = taille du bouton
    // float sizeStartX, sizeStartY;
    // sf::Vector2f startSize = this->getStartSizeRule(sizeStartX, sizeStartY, scaleX, scaleY);

    this->getStartSizeRule(curr._sizeStartX, curr._sizeStartY, scaleX, scaleY);

    // float sizeEndX, sizeEndY;
    float posEndX, posEndY;
    // sf::Vector2f endSize, endPos;
    // endSize = this->getEndSizeRule(sizeEndX, sizeEndY, scaleX, scaleY);
    this->getEndSizeRule(curr._sizeEndX, curr._sizeEndY, scaleX, scaleY);
    if (id == 0){
        // endPos.x = windowSize.x / 2.0f - endSize.x / 2.0f;
        // endPos.y = windowSize.y / 2.0f - endSize.y / 2.0f;
        curr._posEndX = windowSize.x / 2.0f - curr._sizeEndX / 2.0f;
        curr._posEndY = windowSize.y / 2.0f - curr._sizeEndY / 2.0f;
    }
    else if (id == 1){
        curr._posEndX = windowSize.x / 2.0f;
        curr._posEndY = windowSize.y / 2.0f - curr._sizeEndY / 2.0f;
    }
    else if (id == 2){
        curr._posEndX = windowSize.x / 2.0f;
        curr._posEndY = windowSize.y / 3.0f;
    }
    else if (id == 3){
        curr._posEndX = windowSize.x / 2.5f - curr._sizeEndX;
        curr._posEndY = windowSize.y / 4.5f;
    }




    
    // 7. Interpolation position et taille
    // sf::Vector2f currentPos;
    // currentPos.x = startPos.x + (endPos.x - startPos.x) * animationProgress;
    // currentPos.y = startPos.y + (endPos.y - startPos.y) * animationProgress;
    sf::Vector2f currentPos;
    currentPos.x = curr._posStartX + (curr._posEndX - curr._posStartX) * animationProgress;
    currentPos.y = curr._posStartY + (curr._posEndY - curr._posStartY) * animationProgress;

    // sf::Vector2f currentSize;
    // currentSize.x = startSize.x + (endSize.x - startSize.x) * animationProgress;
    // currentSize.y = startSize.y + (endSize.y - startSize.y) * animationProgress;
    sf::Vector2f currentSize;
    currentSize.x = curr._sizeStartX + (curr._sizeEndX - curr._sizeStartX) * animationProgress;
    currentSize.y = curr._sizeStartY + (curr._sizeEndY - curr._sizeStartY) * animationProgress;

    // 8. Appliquer position
    this->_currentSprite.setPosition(currentPos);

    // 9. Appliquer scale en fonction de la taille de la texture
    sf::Vector2u texSize = this->_currentSprite.getTexture()->getSize();
    if (texSize.x == 0 || texSize.y == 0)
        return;  // éviter division par zéro
    sf::Vector2f currentScale;
    currentScale.x = currentSize.x / texSize.x;
    currentScale.y = currentSize.y / texSize.y;

    this->_currentSprite.setScale(currentScale);
    // this->chooseRotation(id);
    this->chooseRotation(curr);

    std::cout << "ID: " << curr._id << "\n"
          << "Start Position: (" << curr._posStartX << ", " << curr._posStartY << ")\n"
          << "End Position: (" << curr._posEndX << ", " << curr._posEndY << ")\n"
          << "Start Size: (" << curr._sizeStartX << ", " << curr._sizeStartY << ")\n"
          << "End Size: (" << curr._sizeEndX << ", " << curr._sizeEndY << ")\n"
          << "Angle: " << curr._angle << "°\n";
}


void GraphicHelp::applyBlur(void) {
    float deltaTime = this->_clock.restart().asSeconds();

    // Limite le deltaTime à un maximum pour éviter une trop grande variation
    const float maxDeltaTime = 0.1f;
    if (deltaTime > maxDeltaTime) {
        deltaTime = maxDeltaTime;
    }
    this->_elapsedTime += deltaTime;
    
    this->_blurProgress = std::min(this->_elapsedTime / this->_blurDuration, 1.0f);
    float easedBlur = this->_blurProgress;
    easedBlur = easedBlur * easedBlur * easedBlur * easedBlur; // ease-in
    // this->ruleAnimation(this->_currentSpriteIndex, this->_blurProgress);
    //initialiser le premier id de la structure
    this->_rulesGame[0].second._id = 0;
    this->ruleAnimation(0, this->_rulesGame[0].second, this->_blurProgress);


    if (this->_elapsedTime >= this->_blurDuration && !this->_spriteDisplayed) {
        this->_displayedSprites.push_back(this->_currentSprite);
        this->_endBlur = true;
        this->_spriteDisplayed = true;
    }

    // Mise à jour de l'intensité du flou
    if (this->_blurActive) {
        this->_blurIntensity = easedBlur;
    } else {
        this->_blurIntensity = 1.0f - easedBlur;
    }
    // Taille de la fenêtre
    int width = this->_graphic->getWidthWin();
    int height = this->_graphic->getHeigthWin();

    // // Création d'une texture temporaire
    sf::RenderTexture blurPass;
    blurPass.create(width, height);
    blurPass.clear();
    blurPass.draw(this->getGraphicMenu()->getCurrentSprite());
    blurPass.display();

    // Application du flou isotrope (shader circulaire)
    const float maxBlurRadius = 30.0f;  // Peut être ajusté

    this->_blur.setUniform("texture", blurPass.getTexture());
    this->_blur.setUniform("radius", this->_blurIntensity * maxBlurRadius);
    
    this->_graphic->getWindow().clear();
    this->_finalSprite.setTexture(blurPass.getTexture());
    //ajouter dans mon tableau le premier sprite
    this->_graphic->getWindow().draw(this->_finalSprite, &this->_blur);
    this->_graphic->getWindow().draw(this->_currentSprite);
    this->_graphic->displayWindow();
}


//*********************************GETTERS*********************************
sf::View &GraphicHelp::getView(void){
    return (this->_view);
}

GraphicMenu *GraphicHelp::getGraphicMenu(void){
    return (this->_graphicMenu);
}

bool &GraphicHelp::getBlur(void){
    return (this->_blurActive);
}

bool &GraphicHelp::getSpriteDisplayed(void){
    return (this->_spriteDisplayed);
}

int &GraphicHelp::getCurrentSpriteIndex(void){
    return (this->_currentSpriteIndex);
}

sf::Sprite &GraphicHelp::getCurrentSprite(void){
    return (this->_currentSprite);
}

std::vector<std::pair<sf::Texture, SpriteAttributes>> &GraphicHelp::getRulesGame(void){
    return (this->_rulesGame);
}

std::vector<sf::Sprite> &GraphicHelp::getDisplayedSprites(void){
    return (this->_displayedSprites);
}

float &GraphicHelp::getElapsedTime(void){
    return (this->_elapsedTime);
}

bool &GraphicHelp::getEndBlur(void){
    return (this->_endBlur);
}

bool &GraphicHelp::getPressEnter(void){
    return (this->_pressEnter);
}

sf::Sprite &GraphicHelp::getFinalSprite(void){
    return (this->_finalSprite);
}

float &GraphicHelp::getBlurProgress(void){
    return (this->_blurProgress);
}

sf::Clock &GraphicHelp::getClock(void){
    return (this->_clock);
}
//*********************************SETTERS*********************************