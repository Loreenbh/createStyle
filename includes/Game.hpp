#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <Graphic.hpp>
// #include <iostream>

enum GameState {
    MENU,
    PLAY,
    HELP,
    QUIT
};

class Game {
    private:
        sf::Event           _event;
        GameState           _state;
        Graphic            *_graphics;
        // Input               *input;
        // Audio               *audio;
        // Scene               *scene;

    public:
        //Constructor
        Game();
        //Destructor
        ~Game();  
    
        //Public Methods
        void    checkButtonMenuPressed();
        void    closeWindow();
        bool    hoverButtonsMenu();
        
        //Getters
        Graphic *getGraphic() const;
        GameState getStatus() const;
        sf::Event   &getEvent();

        //Setters
        GameState setStatus(GameState status);

    };


#endif