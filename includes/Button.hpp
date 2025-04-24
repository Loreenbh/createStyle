#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class Graphic;

struct AttributeButton{
    sf::Text     _text;
    sf::Font      _font;
    std::string  _str;
};

class Button: public sf::RectangleShape {
    private:
        Graphic     *_graphic;
        int         _id;
        AttributeButton _atrButton;
        float   _buttonRefWidth;
        float   _buttonRefHeight;
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