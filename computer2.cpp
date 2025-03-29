#include "computer2.h"


Computer::Computer(Snake& s, Apple& a) : snake(s), apple(a)
{
    
};

void Computer::metric()
{
    int snake_head_x = snake.get_body().front().second;
    int snake_head_y = snake.get_body().front().first;
    int apple_x = apple.get_apple_loc().second;
    int apple_y = apple.get_apple_loc().first;

    given_radius = sqrt( pow(snake_head_x - apple_x, 2) + pow(snake_head_y - apple_y, 2)); 
}

char Computer::decision()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0,1);
    double give = dist(gen);
    
    //if(give <= 0.25)
    //    direction = 'R';
    //else if(give > 0.25 && give <= 0.5)
    //    direction = 'L';
    //else if(give > 0.5 && give <= 0.75)
    //    direction = 'U';
    //else if(give > 0.75)
    //    direction = 'D';

    if(snake.direction == 'L')
    {
        //we know next choice cant be R
        if()

    }
}