#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "graphicMenu.hpp"

class GraphicMenu;

//LANCER LE JEU SI SEULEMENT 2 SPRITES OU PLUS
class Graphic {
    private:

        //Handle window je laisse dans General
        sf::RenderWindow            _window;
        const float                 _ratio;
        unsigned int                _windowWidth;
        unsigned int                _windowHeight;
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
    };


#endif