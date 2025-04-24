#include "timer.h"

Timer::Timer()
{
    start_time = std::chrono::high_resolution_clock::now();
    game_start = start_time;
}

bool Timer::Update()
{
    auto current_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);

    if(elapsed_time >= move_interval)
    {
        start_time = std::chrono::high_resolution_clock::now();
        return true;
    }
    else
        return false;
}

double Timer::totalTime() const
{
    auto current_time = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration<double>(current_time - game_start);
    //return elapsed.count();
    return elapsed.count();
}


