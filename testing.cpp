#include <iostream>
#include "game.h"

int main()
{
    Snake snake;
    Timer timer;
    Apple apple;
    Computer computer(snake, apple);
    Game game(snake, timer, apple, computer);

    //game.set_board();

    std::cout<<"begin? hit Y"<<std::endl;
    char toggle;
    std::cin>>toggle;
    int counter = 1;

    if(toggle == 'Y' || toggle == 'y')
    for(int i = 0; i<50; i++)
    {
        std::cout<<"game: "<<counter<<std::endl;
        while(game.game_toggle())
        {
            game.set_board();
            //game.show_board();
            //std::cout<<std::endl;
            game.update_board();
        }
        computer.episode_states_actions.clear();
        computer.weight_update();
        counter++;
        snake.snake_reset();
        apple.apple_reset();
        game.game_reset();
    }


    return 0;
}

