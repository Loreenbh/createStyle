#ifndef GRAPHICMENU_HPP
#define GRAPHICMENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Graphic;

//LANCER LE JEU SI SEULEMENT 2 SPRITES OU PLUS
class GraphicMenu {
    private:
        Graphic *_graphic;
        int _currentSpriteIndex;
        sf::Sprite _currentSprite;
        std::vector<std::string> _pathSceneMenu;
        std::vector<sf::Texture> _textureMenu;
        sf::Sprite _nextSprite; 
        bool _stopFade;
        bool _fade;
        float _fadeDuration;
        float _waitDuration;
        float _currOpacity;
        sf::Clock _clock;
        
        //Button Help
        sf::Texture _buttonHelpT;
        sf::Sprite _buttonHelpS;
        float _refPosX;
        float _refPosY;
        float _refWidth;
        float _refHeigth;
        sf::Text _buttonTxt;
        sf::Font _buttonFont;

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
        sf::Texture &getHelpButtonTexture(void);
        sf::Sprite &getHelpButton(void);
        sf::Text &getHelpButtonTxt(void);
        float getRefPosX(void);
        float getRefPosY(void);
        float getRefWidth(void);
        float getRefHeigth(void);

        //********Setters*********
        bool &setFade(bool value);

    };


#endif