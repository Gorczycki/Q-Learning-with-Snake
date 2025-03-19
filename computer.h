#ifndef COMPUTER_H
#define COMPUTER_H

#include <vector>
#include <random>
#include "snake.h"
#include "apple.h"

class Computer
{
    public:
        Computer(Snake& snake, Apple& apple);

        //getters:

        //setters:

        void move_generator();

        char move;

        struct features
        {
            double apple_dist;
            char direction;
            bool danger_left;
            bool danger_right;
            bool danger_up;
            bool danged_down;   
        };

        std::vector<double> features;

        
        std::vector<double> weights;
        //+1 for moving closer to apple, -10 for collision, 10 for eating apple
        std::vector<int> rewards = {1,-10,10};

        double Q_S_A;

        //weights:
        double omega_1, omega_2, omega_3, omega_4, omega_5, omega_6;

        double epsilon = 0.2;

        void weight_update();

        //storing states and actions for current epsiode:
        std::vector<std::pair<std::vector<double>, char>> episode_states_actions;
        //the state is represented by the features vector, and the action is "move"

        //need state spaces as a csv, will take a state to be:

        //State: {features}

        Snake& snake;
        Apple& apple;
        const double learning_rate = 0.1;
        const double gamma = 0.9;
        const double alpha = 0.5;
        const double exploration_rate = 0.1;   
        double distance;

        private:     

};

#endif