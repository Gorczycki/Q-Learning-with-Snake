#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
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
    for(int i = 0; i<100; i++)
    {
        while(game.game_toggle())
        {
            game.set_board();
            game.show_board();
            //std::cout<<std::endl;
            game.update_board();
        }
        std::cout<<"game: "<<counter<<", Best game overall has "<<game.max_apples<<" eaten"<<std::endl;
        //computer.episode_states_actions.clear();
        //computer.weight_update();
        counter++;
        snake.snake_reset();
        //snake = std::make_unique<Snake>();
        apple.apple_reset();
        game.game_reset();
    }
        //std::cout<<std::endl;
        //std::cout<<computer.episode_states_actions.size();
        //std::cout<<std::endl;
        //std::cout<<"game: "<<counter<<std::endl;

        //std::cout<<std::endl;
        //game.show_board();

    //game.show_board();

    return 0;
}

