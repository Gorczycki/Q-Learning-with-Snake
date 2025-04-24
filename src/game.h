#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
//#include <SFML/Graphics.hpp>
#include "game.h"
#include "snake.h"
#include "timer.h"
#include "apple.h"
//#include "computer.h"
#include "computer2.h"


//game.cpp takes input from computer.cpp
//computer.cpp will only modify snake and apple, thus we do not need to include "game.h" in computer.h
//when game.cpp modifies snake.cpp, is it reflected in the reference included in computer.cpp?
//keep in mind, game.cpp is master, and testing.cpp just provides function calls and std<<cout;

class Game
{
    public:
        Game(Snake& snake, Timer& timer, Apple& apple, Computer& computer);

        void set_board();

        void update_board(); //based on timer

        bool wall_collision();

        void apple_radius();

        void apple_eaten();

        bool self_collision();

        char set_direction();

        char get_direction(); //from user

        void show_board();

        bool game_toggle() const;

        void set_game_toggle(bool state);

        void board_reset();

        void game_reset();

        void results();

        int apples_eaten;
        int max_apples;

    private:
        std::vector<std::vector<int>> board;
        bool game_on_off = true;
        char direction;
        Snake& snake;
        Timer& timer;
        Apple& apple;
        Computer& computer;

        //Snake* snake_copy;
        //int board_width = 16;
        //int board_height = 14;    

};


#endif 
