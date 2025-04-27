#ifndef GRAPHICHELP_HPP
#define GRAPHICHELP_HPP

#include <SFML/Graphics.hpp>

class Graphic;
#include "Button.hpp"

class GraphicHelp {
    private:
        Button _buttonReturn;
        Graphic *_graphic;
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::View _view;
    public:
        //********Constructor*********
        GraphicHelp(Graphic *graphic);
        //********Destructor*********
        ~GraphicHelp();  
    

        //********Public Methods*********
        void    loadSceneHelp(void);
        void    drawWindowHelp(void);


        //********Getters*********
        sf::View &getView(void);
        sf::Sprite &getSprite(void);


        //********Setters*********

    };


#endif