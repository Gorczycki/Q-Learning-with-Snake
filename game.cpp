#include "game.h"
Game::Game(Snake& s, Timer& t, Apple& a, Computer& c) 
    : board(14, std::vector<int>(16, 0)), 
      snake(s), 
      timer(t), 
      apple(a), 
      computer(c)
{
    apples_eaten = 0;
    max_apples = 0;
}

void Game::set_board()
{
    board_reset();
    for(int i = 0; i < snake.get_body().size(); i++)
    {
        if(!snake.get_body().empty())
        if(i >= 0 && i < snake.get_body().size())
        {
            int x = snake.get_body()[i].first;
            int y = snake.get_body()[i].second;
            if (x >= 0 && x < 16 && y >= 0 && y < 14) {
                board[y][x] = 1; // Set valid positions
            }
            //board[y][x] = 1;
        }
    }
    
    int apple_x = apple.get_apple_loc().first;
    int apple_y = apple.get_apple_loc().second;
    
    board[apple_y][apple_x] = 2;
}

void Game::update_board()
{
    //std::this_thread::sleep_for(std::chrono::milliseconds(400));
    std::this_thread::sleep_for(std::chrono::milliseconds(60));
    bool temp = timer.Update();

    if(temp)
    {
        if(self_collision() == true || wall_collision() == true) //game ender
        {
            set_game_toggle(false);
            results();
        }

        snake.shift_snake();
        
        computer.decision();
        //computer.crude_correction();

        while( (snake.direction == 'R' && computer.move == 'L') || (snake.direction == 'L' && computer.move == 'R') ||
        (snake.direction == 'U' && computer.move == 'D') || (snake.direction == 'D' && computer.move == 'U'))
        {
            //computer.move_generator(); makes sure valid move, computer will need to respond again
            //computer.crude_correction();
            computer.decision();
            //computer.self_collision();
        }
        snake.direction = computer.move; //computer.decision() modifies char move, which is set here

        if(snake.get_head() == apple.get_apple_loc())
        {
            apples_eaten++;
            snake.snake_grow();
            apple_radius();
        }
        if(self_collision() == true || wall_collision() == true)
        {
            set_game_toggle(false);
            results();
        }
    }
    //if(snake.get_head() == apple.get_apple_loc())
    //{
    //    snake.snake_grow();
    //    apple_radius();
    //}
}

bool Game::wall_collision()
{ 
    //???
    if(snake.get_head().first == 16) //was 14
        return true;
    else if(snake.get_head().first == -1)
        return true;
    else if(snake.get_head().second == 14) //was 16
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
        apples_eaten++;
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
    //window.clear();
//
    //for (auto& segment : snake.get_body())
    //{
    //    sf::RectangleShape rect(sf::Vector2f(20.f, 20.f)); // Size of each block in the snake
    //    rect.setPosition(sf::Vector2f(segment.second * 20.f, segment.first * 20.f));  // Position based on snake's coordinates
    //    rect.setFillColor(sf::Color::Green);  // Set the color of the snake
    //    window.draw(rect);  // Draw the segment on the window
    //}
//
    //sf::RectangleShape appleRect(sf::Vector2f(20.f, 20.f));  // Size of the apple
    //appleRect.setPosition(sf::Vector2f(apple.get_apple_loc().second * 20.f, apple.get_apple_loc().first * 20.f));
    //appleRect.setFillColor(sf::Color::Red);  // Set the color of the apple
    //window.draw(appleRect);
//
    //window.display();

    //for(int i = 0; i<board.size(); i++)
    //{
    //    for(int j = 0; j<board[i].size(); j++)
    //    {
    //        std::cout<<board[i][j]<<" ";
    //    }
    //    std::cout<<std::endl;
    //}

    std::ofstream outfile("game_frames.txt", std::ios_base::app);

    for(int i = 0; i<board.size(); i++)
    {
        for(int j = 0; j < board[i].size(); j++)
        {
            outfile << board[i][j];
        }
        outfile<< "\n";
    }

    outfile << "===\n";

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
    //board.clear();
    board = temp;
}

void Game::game_reset()
{
    game_on_off = true;
}

void Game::results()
{
    max_apples = std::max(max_apples,apples_eaten);
    apples_eaten = 0;

    //current game:
    int current_lines = 0;
    std::string line;
    std::ifstream infile_current("game_frames.txt");

    while(getline(infile_current, line))
        current_lines++;
    infile_current.close();



    //best game:
    int max_lines = 0;
    std::ifstream infile_max("max.txt");
    
    while(std::getline(infile_max, line))
        max_lines++;
    infile_max.close();




    if(current_lines > max_lines)
    {
        std::ofstream outfile("max.txt", std::ios::trunc);
        std::ifstream infile_game("game_frames.txt");

        while(std::getline(infile_game, line))
            outfile<<line<<'\n';
        
        infile_game.close();
        outfile.close();
    }

    std::ofstream himfile("game_frames.txt", std::ios::trunc);
}