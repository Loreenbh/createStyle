#ifndef GRAPHICMENU_HPP
#define GRAPHICMENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Graphic;

struct FadeEffect{
    //Constructor
    FadeEffect(bool s, bool f, float fd, float wd, float op, sf::Clock c);
    //Variables
    bool _stopFade;
    bool _fade;
    float _fadeDuration;
    float _waitDuration;
    float _currOpacity;
    sf::Clock _clock;
    //Functions
    bool &setFade(bool value);
};

struct HelpButton{
    //Constructor
    HelpButton(sf::Texture t, sf::Sprite s, sf::Text txt, sf::Font f, float x, 
        float y, float w, float h);
    //Variables
    sf::Texture _buttonHelpT;
    sf::Sprite _buttonHelpS;
    sf::Text _buttonTxt;
    sf::Font _buttonFont;
    float _refPosX;
    float _refPosY;
    float _refWidth;
    float _refHeigth;
    //Getters
    sf::Texture &getHelpButtonTexture(void);
    sf::Sprite &getHelpButtonSprite(void);
    sf::Text &getHelpButtonTxt(void);
    float getRefPosX(void);
    float getRefPosY(void);
    float getRefWidth(void);
    float getRefHeigth(void);

};

//LANCER LE JEU SI SEULEMENT 2 SPRITES OU PLUS
class GraphicMenu {
    private:
        Graphic *_graphic;
        FadeEffect _fadeEffect;
        HelpButton _helpButton;
        int _currentSpriteIndex;
        sf::Sprite _currentSprite;
        std::vector<std::string> _pathSceneMenu;
        std::vector<sf::Texture> _textureMenu;
        sf::Sprite _nextSprite;

    public:
        //********Constructor*********
        GraphicMenu(Graphic *graphic);
        //********Destructor*********
        ~GraphicMenu();  
    
        //********Public Methods*********
        void loadSceneMenu(void);
        void drawWindowMenu(void);
        void animationSlideMenu(void);
        void getReadyNext(void);
        void createButton(void);
        void setSprite(std::string path, sf::Sprite &sprite, sf::Texture &texture);
        
        //********Getters*********
        bool &getFade(void);
        sf::Sprite &getCurrentSprite(void);
        int &getCurrentIndex(void);
        sf::Texture &getCurrentTexture(void);
        HelpButton &getHelpButton(void);
        FadeEffect &getFadeEffect(void);

        //********Setters*********

    };


#endif