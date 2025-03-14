#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

//grow the snake from apple, shift the snake through time, retreive snake body
//functions such as collision with wall will be handled in game.cpp
//need to silo each .cpp file, as in keep snake.cpp and apple.cpp separate

//the snake body will simply follow the head, so when we deal with a direction change, change position of head,
//and then head - 1 will become head, head-2 will become head-1

class Snake
{
    public:
        Snake();

        void snake_grow();

        //dependent on time increment from time.cpp:
        void shift_snake();

        //change_direction(Game& game), takes input from game.cpp
        //void change_direction()
        //{
        //    direction = 'R'; // for example
        //}

        std::vector<std::pair<int, int>> get_body();

        char snake_get_direction();

        std::pair<int, int> get_head();

    private:
        char direction;
        std::vector<std::pair<int, int>> body;


};





#endif