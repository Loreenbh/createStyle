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
        sf::Event _event;
        GameState _state;
        Graphic *_graphics;
        // Input               *input;
        // Audio               *audio;
        // Scene               *scene;

    public:
        //********Constructor*********
        Game();
        //********Destructor*********
        ~Game();  
    

        //********Public Methods*********
        void closeWindow(void);
                    //Menu
        void checkButtonMenuPressed(void);
        bool hoverButtonsMenu(void);
        void selectEventMenu(void);
                    //Help
        void selectEventHelp(void);


        //*********Getters**************
        Graphic *getGraphic(void) const;
        GameState &getStatus(void);
        sf::Event &getEvent(void);


        //*********Setters**************
        GameState &setStatus(GameState status);

    };


#endif