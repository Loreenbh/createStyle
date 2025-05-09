#ifndef GRAPHICHELP_HPP
#define GRAPHICHELP_HPP

#include <SFML/Graphics.hpp>

class Graphic;

// struct SpriteAnimationState {
//     float elapsedTime = 0.f;
//     float progress = 0.0f;
//     bool displayed = false;
// };

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

        //Load sprites rules
        std::vector<std::string> _pathRulesGame;
        std::vector<sf::Texture> _rulesGame;
        std::vector<sf::Sprite> _displayedSprites;
        bool _spriteDisplayed;
        bool _endBlur;
        bool _pressEnter;
        //-----------------------
        float _refRuleStartX;
        float _refRuleStartY;
        float _refRuleEnd;
        //POST1
        float _refRule1PosX;
        float _refRule1PosY;
        //POST2
        float _refRule2PosX;
        float _refRule2PosY;

    public:
        //********Constructor*********
        GraphicHelp(Graphic *graphic, GraphicMenu *graphicMenu);
        //********Destructor*********
        ~GraphicHelp();  
    

        //********Public Methods*********
        void loadSceneHelp(void);
        void applyBlur(void);
        void ruleAnimation(int id, float animationProgress);
        sf::Vector2f getStartPosRule(float &x, float &y, float scaleX, float scaleY);
        sf::Vector2f getStartSizeRule(float &w, float &h, float scaleX, float scaleY);
        sf::Vector2f getEndSizeRule(float &w, float &h, float scaleX, float scaleY);
        void chooseRotation(int id);
        void drawBlurBackground(void);

        //********Getters*********
        sf::View &getView(void);
        GraphicMenu *getGraphicMenu(void);
        bool &getBlur(void);
        bool &getSpriteDisplayed(void);
        int &getCurrentSpriteIndex(void);
        sf::Sprite &getCurrentSprite(void);
        std::vector<sf::Texture> &getRulesGame(void);
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