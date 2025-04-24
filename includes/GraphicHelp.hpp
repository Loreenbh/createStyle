#ifndef GRAPHICHELP_HPP
#define GRAPHICHELP_HPP

#include <SFML/Graphics.hpp>

class Graphic;
#include "Button.hpp"

class GraphicHelp {
    private:
        Button      _buttonReturn;
        Graphic     *_graphic;
        sf::Sprite  _sprite;
        sf::View    _view;
    public:
        //Constructor
        GraphicHelp(Graphic *graphic);

        //Destructor
        ~GraphicHelp();  
    
        //Public Methods
        void    loadSceneHelp(void);
        void    drawWindowHelp(void); //scroller la fenetre

        //Getters
        sf::View &getView();
        sf::Sprite &getSprite();

    };


#endif