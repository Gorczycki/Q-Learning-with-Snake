#include "game.h"
#include <cmath>

Game::Game(Snake& s, Timer& t, Apple& a, Computer& c) 
    : board(14, std::vector<int>(16, 0)), snake(s), timer(t), apple(a), computer(c)
{
    
}

void Game::set_board()
{
    board_reset();
    for(int i = 0; i < snake.get_body().size(); i++)
    {
        int x = snake.get_body()[i].first;
        int y = snake.get_body()[i].second;
        if (x >= 0 && x < 16 && y >= 0 && y < 14) {
            board[y][x] = 1; // Set valid positions
        }
    }
    int apple_x = apple.get_apple_loc().first;
    int apple_y = apple.get_apple_loc().second;
    if (apple_x >= 0 && apple_x < 16 && apple_y >= 0 && apple_y < 14) {
        board[apple_y][apple_x] = 2; // Set valid apple position
    }
}

void Game::update_board()
{
    //std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    bool temp = timer.Update();

    if(temp)
    {
        if(self_collision() == true || wall_collision() == true)
            set_game_toggle(false);
        snake.shift_snake();
        computer.move_generator();
        while( (snake.direction == 'R' && computer.move == 'L') || (snake.direction == 'L' && computer.move == 'R') ||
        (snake.direction == 'U' && computer.move == 'D') || (snake.direction == 'D' && computer.move == 'U'))
        {
            computer.move_generator(); //makes sure valid move, computer will need to respond again
        }
        snake.direction = computer.move;

        if(snake.get_head() == apple.get_apple_loc())
        {
            snake.snake_grow();
            apple_radius();
        }
        if(self_collision() == true || wall_collision() == true)
            set_game_toggle(false);
    }
    //if(snake.get_head() == apple.get_apple_loc())
    //{
    //    snake.snake_grow();
    //    apple_radius();
    //}
}

bool Game::wall_collision()
{
    if(snake.get_head().first == 14)
        return true;
    else if(snake.get_head().first == -1)
        return true;
    else if(snake.get_head().second == 16)
        return true;
    else if(snake.get_head().second == -1)
        return true;

    return false;
}   

void Game::apple_radius()
{
    double desired_radius = 3;
    int snake_head_x = snake.get_body().front().second;
    int snake_head_y = snake.get_body().front().first;
    int apple_x = apple.get_apple_loc().second;
    int apple_y = apple.get_apple_loc().first;

    double actual_radius = sqrt( pow(snake_head_x - apple_x, 2) + pow(snake_head_y - apple_y, 2));

    while(actual_radius <= desired_radius)
    {
        apple.place_apple();
        apple_x = apple.get_apple_loc().second;
        apple_y = apple.get_apple_loc().first;
        actual_radius = sqrt( pow(snake_head_x - apple_x, 2) + pow(snake_head_y - apple_y, 2));
    }
}

void Game::apple_eaten()
{
    if(snake.get_head() == apple.get_apple_loc())
    {
        snake.snake_grow();
    }
}

bool Game::self_collision()
{
    for(int i = 1; i<snake.get_body().size(); i++)
    {
        if(snake.get_head() == snake.get_body()[i])
            return true;
    }
    return false;
}

char Game::set_direction()
{
    return snake.snake_get_direction();
}

char Game::get_direction()
{
    return snake.snake_get_direction();
}

void Game::show_board()
{
    for(int i = 0; i<board.size(); i++)
    {
        for(int j = 0; j<board[i].size(); j++)
        {
            std::cout<<board[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

bool Game::game_toggle() const
{
    return game_on_off;
}

void Game::set_game_toggle(bool state)
{
    game_on_off = state;
}

void Game::board_reset()
{
    std::vector<std::vector<int>> temp(14, std::vector<int>(16, 0));
    board = temp;
}

void Game::game_reset()
{
    game_on_off = true;
}