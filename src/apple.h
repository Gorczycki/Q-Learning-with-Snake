#ifndef APPLE_H
#define APPLE_H

#include <vector>

class Apple
{
    public:
        Apple();

        void place_apple();

        std::pair<int, int> get_apple_loc();

        void apple_reset();

    private:
        std::pair<int, int> apple_loc;
};

#endif
