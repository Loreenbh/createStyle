#include "Graphic.hpp"

//*********************************CONSTRUCTORS*********************************
GraphicHelp::GraphicHelp(Graphic *graphic, GraphicMenu *GraphicMenu) : 
_graphic(graphic),
_graphicMenu(GraphicMenu),
_view(sf::FloatRect(0, 0, this->_graphic->getWidthWin(), this->_graphic->getHeigthWin())),
_blurIntensity(0.0f),
_blurDuration(1.5f),
_blurActive(false),
_blurProgress(0.0f),
_elapsedTime(0.0f),
_clock(),
_currentSprite(),
_currentSpriteIndex(0),
_refRule1PosX(250),
_refRule1PosY(100),
_refRuleStartX(550),
_refRuleStartY(500),
_refRuleEnd(400),
_spriteDisplayed(false),
_endBlur(false),
_pressEnter(false),
_finalSprite()
{
    _pathRulesGame.push_back("../scenes/sceneHelp/rules01.png");
    _pathRulesGame.push_back("../scenes/sceneHelp/rules02.png");
    _pathRulesGame.push_back("../scenes/sceneHelp/rules03.png");

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
        this->_rulesGame.push_back(std::move(texture)); 
    }
    //je set juste la premiere texture
    this->_currentSprite.setTexture(this->_rulesGame[this->_currentSpriteIndex]);
    this->_graphic->adaptHeightToWin(this->_rulesGame[this->_currentSpriteIndex], this->_currentSprite);
}

sf::Vector2f GraphicHelp::getStartPosRule(float &x, float &y, float scaleX, float scaleY){
    if (this->_currentSpriteIndex == 0){  
        x = this->getGraphicMenu()->getRefPosX() * scaleX;
        y = this->getGraphicMenu()->getRefPosY() * scaleY;
    }
    else if (this->_currentSpriteIndex == 1){  
        x = 100 * scaleX;
        y = 100 * scaleY;
    }
    else if (this->_currentSpriteIndex == 3){  
        x = 100 * scaleX;
        y = 300 * scaleY;
    }
    return sf::Vector2f(x, y);
}


sf::Vector2f GraphicHelp::getStartSizeRule(float &w, float &h, float scaleX, float scaleY){
    if (this->_currentSpriteIndex == 0){
        w = this->getGraphicMenu()->getHelpButton().getGlobalBounds().width * scaleX;
        h = this->getGraphicMenu()->getHelpButton().getGlobalBounds().height * scaleY;
    }
    else{
        w = this->_refRuleEnd * scaleX * 3;
        h = this->_refRuleEnd * scaleY * 3;
    }
    return sf::Vector2f(w, h);
}

sf::Vector2f GraphicHelp::getEndSizeRule(float &w, float &h, float scaleX, float scaleY){
    w = this->_refRuleEnd * scaleX;
    h = this->_refRuleEnd * scaleY;
    return sf::Vector2f(w, h);
}

void GraphicHelp::chooseRotation(int id){
    if (id == 0)
        this->_currentSprite.setRotation(10);
    else if (id == 1)
        this->_currentSprite.setRotation(-30);
    else if (id == 2)
        this->_currentSprite.setRotation(20);
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
    // this->_graphic->getWindow().draw(this->_displayedSprites[0]);
    // this->_graphic->displayWindow();
}


void GraphicHelp::ruleAnimation(int id, float animationProgress) {
    if (id >= 1){
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
    float posStartX, posStartY;
    sf::Vector2f startPos = this->getStartPosRule(posStartX, posStartY, scaleX, scaleY);

    // 4. Taille départ = taille du bouton
    float sizeStartX, sizeStartY;
    sf::Vector2f startSize = this->getStartSizeRule(sizeStartX, sizeStartY, scaleX, scaleY);

    float sizeEndX, sizeEndY;
    float posEndX, posEndY;
    sf::Vector2f endSize, endPos;
    endSize = this->getEndSizeRule(sizeEndX, sizeEndY, scaleX, scaleY); //endsize.x et endsize.y
    if (id == 0){ //la position 
        endPos.x = windowSize.x / 2.0f - endSize.x / 2.0f;
        endPos.y = windowSize.y / 2.0f - endSize.y / 2.0f;
    }
    else if (id == 1){
        endPos.x = 250;
        endPos.y = 80;
    }
    else if (id == 2){
        endPos.x = 260;
        endPos.y = 120;
    }
    // 7. Interpolation position et taille
    sf::Vector2f currentPos;
    currentPos.x = startPos.x + (endPos.x - startPos.x) * animationProgress;
    currentPos.y = startPos.y + (endPos.y - startPos.y) * animationProgress;

    sf::Vector2f currentSize;
    currentSize.x = startSize.x + (endSize.x - startSize.x) * animationProgress;
    currentSize.y = startSize.y + (endSize.y - startSize.y) * animationProgress;

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
    this->chooseRotation(id);
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
    this->ruleAnimation(this->_currentSpriteIndex, this->_blurProgress);

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

std::vector<sf::Texture> &GraphicHelp::getRulesGame(void){
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