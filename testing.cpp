#include <iostream>
#include "game.h"

int main()
{
    Snake snake;
    Timer timer;
    Apple apple;
    Game game(snake, timer, apple);

    //game.set_board();

    std::cout<<"begin? hit Y"<<std::endl;
    char toggle;
    std::cin>>toggle;
    if(toggle == 'y' || toggle == 'Y')
    {
        while(game.game_toggle())
        {
            game.set_board();
            game.show_board();
            std::cout<<std::endl;
            game.update_board();

            if(game.self_collision() || game.wall_collision())
                game.set_game_toggle(false);
        }
    }

    return 0;
}

