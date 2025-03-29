#ifndef COMPUTER2_H
#define COMPUTER2_H
#include "snake.h"
#include "apple.h"
#include <vector>
#include <random>

class Computer
{
    public:
        Computer(Snake& snake, Apple& apple);

        void metric();

        char decision();

    private:
        double test_var;
        double given_radius;
        double pot_radius;
        char direction;
        Snake& snake;
        Apple& apple;


};

#endif