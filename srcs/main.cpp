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
            if (game->getStatus() == MENU){
                game->selectEventMenu();
                // game->hoverButtonsMenu();
                // if (game->getEvent().type == sf::Event::MouseButtonPressed)
                //     game->checkButtonMenuPressed(); //ici je change le set le type
            }
            if (game->getStatus() == HELP){
                if (game->getEvent().type == sf::Event::MouseButtonPressed){
                    game->getGraphic()->getGraphicHelp()->drawWindowHelp();
                }
                else if (game->getEvent().type == sf::Event::MouseWheelScrolled){
                    game->getGraphic()->handleHelpAnimation(game->getEvent());
                }
            }
            if (game->getEvent().type == sf::Event::Closed)
                game->closeWindow();
        }
        if (game->getStatus() ==  MENU &&  !game->getGraphic()->getGraphicMenu()->isAnimated())
            game->getGraphic()->handleMenuAnimation();
    }
    delete(game);
    return (0);
}


//Dans le menu:
//Animation en boucle : fondu + affichage des boutons --> seulement si false
//Quand je survole un bouton, je met true quand je quitte je remet false;
