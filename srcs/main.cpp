#include "Game.hpp"

int main()
{
    Game *game = nullptr;
    try{
        game = new Game();
    }
    catch(const std::exception &e){
        std::cerr << "Error: " << e.what() << std::endl;
        delete (game);
        return (1);
    }
    if (!game)
        return (1);
    while (game->getGraphic()->isWindowOpen()) {
        game->getEvent();
        while (game->getGraphic()->getWindow().pollEvent(game->getEvent())){
            if (game->getStatus() == MENU)
                game->selectEventMenu();
            else if (game->getStatus() == HELP)
                game->selectEventHelp(); 
            if (game->getEvent().type == sf::Event::Closed)
                game->closeWindow();
        }
        if (game->getStatus() ==  MENU)
            game->getGraphic()->handleMenuAnimation();
        else if (game->getStatus() == HELP){
            game->getGraphic()->getGraphicHelp()->drawWindowHelp();
        }
    }
    delete(game);
    return (0);
}
