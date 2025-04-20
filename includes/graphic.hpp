#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>


//LANCER LE JEU SI SEULEMENT 2 SPRITES OU PLUS
class Graphic {
    private:
        //Handle window
        sf::RenderWindow            _window;
        const float                 _ratio;
        unsigned int                _windowWidth;
        unsigned int                _windowHeight;
        
        //Texture
        int                         _currentSpriteIndex;
        sf::Sprite                  _currentSpriteMenu;
        std::vector<std::string>    _pathBackgroundMenu;
        std::vector<sf::Texture>    _textureMenu;
        
        //animationSlide
        bool                        _fade;
        bool                        _waiting;
        float                       _fadeDuration;
        float                       _waitDuration;
        float                       _currOpacity;
        sf::Clock                   _clock;  // Clock pour gérer le timing du changement de fond
        sf::Sprite                  _nextSprite;

    public:
        //Constructor
        Graphic(int windowWidth, int windowHeight);
        //Destructor
        ~Graphic();  
    
        //Public Methods
        void   adjustWinSize(); //Classe générale graphic
        void   createWindow(); //Classe générale graphic
        int    loadBackgroundMenu(); //dans la classe menu
        void   adaptHeightToWin(sf::Texture &texture, sf::Sprite &sprite); //Classe générale graphic
        bool   isWindowOpen(); //Classe générale graphic
        void   clearWindow(); //Classe générale graphic
        void   displayWindow(); //Classe générale graphic
        void   drawWindowMenu(); //Classe générale graphic
        void   animationSlideMenu();
        void   getReadyNext();

        //Getters
        const sf::RenderWindow  &getWindow() const;
        sf::Sprite              &getSlideMenu();
        bool                    &getTurn();
    };


#endif