#include "game.hpp"

int main()
{
    Game *game = nullptr;
    try{
        game = new Game();
    }
    catch(const std::exception &e){
        std::cerr << "Error: " << e.what() << std::endl;
        delete (game);
        return 1;
    }
    if (!game)
        return (1);
    while (game->getGraphic()->isWindowOpen()) {
        if (game->getStatus() ==  MENU)
            game->getGraphic()->handleMenuAnimation();
    }
    delete(game);
    return (0);
}