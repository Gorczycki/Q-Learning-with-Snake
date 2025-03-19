#include "apple.h"
#include <random>

Apple::Apple()
{
    apple_loc = {10,7};
}

void Apple::place_apple()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib1(0,16);
    std::uniform_int_distribution<int> distrib2(0,14);

    apple_loc.first = distrib1(gen);
    apple_loc.second = distrib2(gen);
}

std::pair<int, int> Apple::get_apple_loc()
{
    return apple_loc;
}

void Apple::apple_reset()
{
    apple_loc = {10,7};
}