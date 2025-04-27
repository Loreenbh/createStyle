#ifndef GRAPHICMENU_HPP
#define GRAPHICMENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Graphic;
#include "Button.hpp"

//LANCER LE JEU SI SEULEMENT 2 SPRITES OU PLUS
class GraphicMenu {
    private:
        Graphic *_graphic;
        int _currentSpriteIndex;
        sf::Sprite _currentSprite;
        std::vector<std::string> _pathSceneMenu;
        std::vector<sf::Texture> _textureMenu;
        bool _stopAnimation;
        bool _fade;
        float _fadeDuration;
        float _waitDuration;
        float _currOpacity;
        sf::Clock _clock;
        sf::Sprite _nextSprite;
        Button _buttonHelp;
        Button _buttonPlay;

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
        
        //********Getters*********
        Button &getButtonPlay(void);
        Button &getButtonHelp(void);
        bool &getAnimation(void);
        sf::Sprite &getCurrentSprite(void);
        int &getCurrentIndex(void);
        sf::Texture &getCurrentTexture(void);


        //********Setters*********
        bool &setAnimation(bool value);

    };


#endif