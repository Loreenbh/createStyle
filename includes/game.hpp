#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <graphic.hpp>
#include <iostream>
#include <vector>

enum GameState {
    MENU,
    GAME,
    OPTIONS,
    QUIT
};

class Game {
    private:
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
        // //Getters
        Graphic *getGraphic() const;
    };


#endif