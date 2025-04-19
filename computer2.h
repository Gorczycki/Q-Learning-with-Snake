#ifndef COMPUTER2_H
#define COMPUTER2_H
#include "snake.h"
#include "apple.h"
#include <vector>
#include <random>
#include <algorithm>
#include <utility>
#include <map>


class Computer
{
    public:
        Computer(Snake& snake, Apple& apple);

        //void metric();

        //void distances();

        void decision();

        bool self_collision(char move_);

        void crude_correction();

        void policy_func();

        //void weight_update();

        char move;  

        struct State{
            int dx;
            int dy;
            char current_dir;
            bool danger_ahead;
            bool danger_left;
            bool danger_right;
            bool danger_up;
            bool danger_down;
        };

        void chooseAction(State state);

        //void Computer::updateQ(State state, char action, float reward, State next_state);

    private:
        char direction;
        double epsilon = 0.98;
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







        const float reward_apple = 10.0;
        const float reward_death = -10.0;
        const float reward_step = -0.1;

        std::map<State, std::map<char, float>> Q_table;

        float alpha = 0.1;
        float gamma = 0.9;

};

#endif