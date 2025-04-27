#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "GraphicMenu.hpp"
#include "GraphicHelp.hpp"

//LANCER LE JEU SI SEULEMENT 2 SPRITES OU PLUS
class Graphic {
    private:
        sf::RenderWindow _window;
        const float _ratio;
        float _windowWidth;
        float _windowHeight;
        float _windowRefWidth;
        float _windowRefHeight;
        float _windowRefMaxWidth;
        float _windowRefMaxHeight;
        GraphicMenu *_graphicMenu;
        GraphicHelp *_graphicHelp;
    
    public:
        //********Constructor*********
        Graphic(int windowWidth, int windowHeight);
        //********Destructor*********
        ~Graphic();  
    
        
        //********Public Methods*********
        void adjustWinSize(void);
        void createWindow(void);
        void adaptHeightToWin(sf::Texture &texture, sf::Sprite &sprite);
        bool isWindowOpen(void);
        void clearWindow(void);
        void displayWindow(void);
                //GraphicMenu
        void initGraphicMenu(void);
        void handleMenuAnimation(void);
        
                //GraphicHelp
        void initGraphicHelp(void);
        void handleHelpAnimation(void);


        //********Getters*********
        sf::RenderWindow &getWindow(void);
        float &getRefWinWidth(void);
        float &getRefWinHeight(void);
        float &getWidthWin(void);
        float &getHeigthWin(void);
        GraphicMenu *getGraphicMenu(void);
        GraphicHelp *getGraphicHelp(void);

    };


#endif