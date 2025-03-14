#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include "game.h"
#include "snake.h"
#include "timer.h"
#include "apple.h"

class Game
{
    public:
        Game(Snake& snake, Timer& timer, Apple& apple);

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

    private:
        std::vector<std::vector<int>> board;
        bool game_on_off = true;
        int apples_eaten;
        char direction;
        Snake& snake;
        Timer& timer;
        Apple& apple;
};


#endif 