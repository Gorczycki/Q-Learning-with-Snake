#include "snake.h"

#include <iostream>

int main()
{
    Snake snake;

    std::vector<std::pair<int, int>> test = snake.get_body();

    for (const auto& row : test)
    {
        std::cout<<row.first<<" "<<row.second<<std::endl;
    }

    std::cout<<std::endl;

    snake.shift_snake();

    test = snake.get_body(); //does this mean get_body() is dependent on calling snake_grow?

    //std::vector<std::pair<int, int>> test = snake.get_body();

    for (const auto& row : test)
    {
        std::cout<<row.first<<" "<<row.second<<std::endl;
    }

    //std::cout<<test.front().first<<" "<<test.front().second;
    //std::cout<<std::endl;
    //std::cout<<test.back().first<<" "<<test.back().second;

    return 0;
}