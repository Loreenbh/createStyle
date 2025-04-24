#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "GraphicMenu.hpp"
#include "GraphicHelp.hpp"

//LANCER LE JEU SI SEULEMENT 2 SPRITES OU PLUS
class Graphic {
    private:
        sf::RenderWindow            _window;
        const float                 _ratio;
        float                _windowWidth;
        float                _windowHeight;
        float                _windowRefWidth;
        float                _windowRefHeight;
        float                _windowRefMaxWidth;
        float                _windowRefMaxHeight;
        GraphicMenu                 *_graphicMenu;
        GraphicHelp                 *_graphicHelp;
    
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
        //Methods GraphicMenu
        void   initGraphicMenu();
        void   handleMenuAnimation();
        
        //Methods GraphicHelp
        void   initGraphicHelp();
        void   handleHelpAnimation(sf::Event &event);

        //Getters
        sf::RenderWindow &getWindow();
        float &getRefWinWidth();
        float &getRefWinHeight();
        float &getWidthWin();
        float &getHeigthWin();
        GraphicMenu  *getGraphicMenu(void);
        GraphicHelp  *getGraphicHelp(void);

    };


#endif