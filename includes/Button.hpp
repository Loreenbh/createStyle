#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
// #include "graphic.hpp"

class Graphic;

class Button: public sf::RectangleShape {
    private:
        Graphic     *_graphic;
        int         _id;
        sf::Text     _text;
        sf::Font      _font;
        std::string  _str;
        float   _buttonRefWidth; //116
        float   _buttonRefHeight; //22
        float   _helpRefX;
        float   _helpRefY;
        float   _playRefX;
        float   _playRefY;
    public:
        //Constructor
        Button(std::string txt, Graphic *graphic, int n);
        //Destructor
        ~Button();  
    
        //Public Methods
        void    setButtonMenu();

        //Getters
        sf::Text &getText();
    };


#endif