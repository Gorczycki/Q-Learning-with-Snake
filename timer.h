#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <thread>
#include <utility>
#include <functional>
    
class Timer
{
    public:
        Timer();

        bool Update();

        double totalTime() const;

    private:
        std::chrono::high_resolution_clock::time_point start_time;
        const std::chrono::milliseconds move_interval = std::chrono::milliseconds(300);
        std::chrono::high_resolution_clock::time_point game_start;
        std::chrono::milliseconds elapsed_time;

};


#endif