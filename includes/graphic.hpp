#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
// #include <cmath>
#include "graphicMenu.hpp"

//LANCER LE JEU SI SEULEMENT 2 SPRITES OU PLUS
class Graphic {
    private:
        sf::RenderWindow            _window;
        const float                 _ratio;
        float                _windowWidth;
        float                _windowHeight;
        float                _windowRefWidth;
        float                _windowRefHeight;
        GraphicMenu                 *_graphicMenu;
    
    public:
        //Constructor
        Graphic(int windowWidth, int windowHeight);
        //Destructor
        ~Graphic();  
    
        //Public Methods
        void   adjustWinSize();
        void   createWindow();
        void   adaptHeightToWin(sf::Texture &texture, sf::Sprite &sprite);
        bool   isWindowOpen();
        void   clearWindow();
        void   displayWindow();
        void   initGraphicMenu();
        void   handleMenuAnimation();

        //Getters
        sf::RenderWindow &getWindow();
        float &getRefWinWidth();
        float &getRefWinHeight();
    };


#endif