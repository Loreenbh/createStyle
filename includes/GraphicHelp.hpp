#ifndef GRAPHICHELP_HPP
#define GRAPHICHELP_HPP

#include <SFML/Graphics.hpp>

class Graphic;

struct SpriteAttributes {
    //Constructor
    SpriteAttributes();
    SpriteAttributes(int i, float psx, float psy, float pex, float pey,
        float sizeSX, float sizeSY, float sizeEX, float sizeEY, float a);
    int _id;
    float _posStartX;
    float _posStartY;
    float _posEndX;
    float _posEndY;
    float _sizeStartX;
    float _sizeStartY;
    float _sizeEndX;
    float _sizeEndY;
    float _angle;
};

class GraphicHelp {
    private:
        Graphic *_graphic;
        GraphicMenu *_graphicMenu;
        sf::Texture _texture;
        sf::Sprite _currentSprite;
        int _currentSpriteIndex;

        // Blur effect
        sf::View _view;
        sf::Shader _blur;
        float _blurDuration;
        sf::Clock _clock;
        float _blurIntensity;
        bool _blurActive;
        float _blurProgress;
        float _elapsedTime;
        sf::Sprite _finalSprite;
        bool _endBlur;

        //Rules
        std::vector<std::string> _pathRulesGame;
        // std::vector<sf::Texture> _rulesGame;
        std::vector<std::pair<sf::Texture, SpriteAttributes>> _rulesGame;
        std::vector<sf::Sprite> _displayedSprites;
        bool _spriteDisplayed;
        bool _pressEnter;
        float _refSizeEnd;
        float _refStartPosX;
        float _refStartPosY;
 
    public:
        //********Constructor*********
        GraphicHelp(Graphic *graphic, GraphicMenu *graphicMenu);
        //********Destructor*********
        ~GraphicHelp();  
    

        //********Public Methods*********
        void loadSceneHelp(void);
        void applyBlur(void);
        // void ruleAnimation(int id, float animationProgress);
        void ruleAnimation(int id, SpriteAttributes &curr, float animationProgress);
        void getStartPosRule(float &x, float &y, float scaleX, float scaleY);
        void getStartSizeRule(float &w, float &h, float scaleX, float scaleY);
        void getEndSizeRule(float &w, float &h, float scaleX, float scaleY);
        void chooseRotation(SpriteAttributes &curr);
        void drawBlurBackground(void);

        //********Getters*********
        sf::View &getView(void);
        GraphicMenu *getGraphicMenu(void);
        bool &getBlur(void);
        bool &getSpriteDisplayed(void);
        int &getCurrentSpriteIndex(void);
        sf::Sprite &getCurrentSprite(void);
        // std::vector<sf::Texture> &getRulesGame(void);
        std::vector<std::pair<sf::Texture, SpriteAttributes>> &getRulesGame(void);
        std::vector<sf::Sprite> &getDisplayedSprites(void);
        float &getElapsedTime(void);
        bool &getEndBlur(void);
        bool &getPressEnter(void);
        sf::Sprite &getFinalSprite(void);
        float &getBlurProgress(void);
        sf::Clock &getClock(void);

        //********Setters*********

    };


#endif