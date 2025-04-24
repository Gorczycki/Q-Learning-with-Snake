#ifndef COMPUTER2_H
#define COMPUTER2_H
#include "snake.h"
#include "apple.h"
#include <vector>
#include <random>
#include <algorithm>
#include <utility>
#include <map>
#include <fstream>
#include <sstream>

using State = std::tuple<int, int, char, bool, bool, bool, bool>;

class Computer
{
    public:
        Computer(Snake& snake, Apple& apple);

        void decision();

        bool self_collision(char move_);

        void getstate();

        void master_move();

        void q_decision();

        void updateq();

        char move; 

        void saveQTable(const std::string& filename);
        void loadQTable(const std::string& filename);

    private:
        char direction;
        double epsilon = 0.99;
        bool collision;
        Snake& snake;
        Apple& apple;

        int snake_head_x;
        int snake_head_y;
        int apple_y;
        int apple_x;
        double radius_1;
        double radius_2;
        double radius_3;
        double radius_4;
        std::map<char, int> matches;
        int choice;

        State state;
        State prev_state;

        std::map<State, std::map<char, double>> Qtable;

        const float reward_apple = 10.0;
        const float reward_death = -10.0;
        const float reward_step = -0.1;

        float alpha = 0.3;
        float gamma = 0.9;

};

#endif
