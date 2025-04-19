//contains crude decision function

#include "computer2.h"


Computer::Computer(Snake& s, Apple& a) : snake(s), apple(a)
{
    direction = 'R';
    collision = false;  
};


//introduce a heuristic to begin     crowding/folding the snake as in human games, with leaving a cell on the
//ends to allow escape. f(x) represents minimizing distance from snake head to snake tail,
//g(x) represents minimizing area of the snake, as in we imagine filled in cells to create a rectangle around the
//snake's width and height. g(x) may also need to handle avoiding self-collisions and wall-collisions


void Computer::decision()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0, 1);
    double give = dist(gen);  // Random move occurrence x% of the time
    double give2 = dist(gen); // Random vs. determined move decision

    if (give2 >= epsilon)
    {
        // Random move selection
        if (give <= 0.25)
            direction = 'R';
        else if (give <= 0.5)
            direction = 'L';
        else if (give <= 0.75)
            direction = 'U';
        else
            direction = 'D';
    }
    else
    {
        // Compute best move by reducing Manhattan distance to apple
        snake_head_y = snake.get_body().front().second;
        snake_head_x = snake.get_body().front().first;
        apple_y = apple.get_apple_loc().second;
        apple_x = apple.get_apple_loc().first;

        // Use Manhattan distance for efficiency
        std::vector<std::pair<char, int>> moves = {
            {'R', std::abs((snake_head_x + 1) - apple_x) + std::abs(snake_head_y - apple_y)},
            {'L', std::abs((snake_head_x - 1) - apple_x) + std::abs(snake_head_y - apple_y)},
            {'U', std::abs(snake_head_x - apple_x) + std::abs((snake_head_y + 1) - apple_y)},
            {'D', std::abs(snake_head_x - apple_x) + std::abs((snake_head_y - 1) - apple_y)}
        };

        // Filter out the opposite direction of the current movement
        std::vector<std::pair<char, int>> valid_moves;
        for (auto &m : moves)
        {
            if ((snake.direction == 'R' && m.first == 'L') ||
                (snake.direction == 'L' && m.first == 'R') ||
                (snake.direction == 'U' && m.first == 'D') ||
                (snake.direction == 'D' && m.first == 'U'))
            {
                continue;
            }
            valid_moves.push_back(m);
        }

        // Choose the move with the minimum distance
        if (!valid_moves.empty())
        {
            direction = valid_moves.front().first;
            int min_distance = valid_moves.front().second;
            for (auto &m : valid_moves)
            {
                if (m.second < min_distance)
                {
                    min_distance = m.second;
                    direction = m.first;
                }
            }
        }
        else
        {
            // Failsafe: If no valid move, choose a random one
            std::vector<char> fallback_moves = {'R', 'L', 'U', 'D'};
            direction = fallback_moves[rand() % 4];
        }
    }
    move = direction;
}

void Computer::self_collision()
{
    // Copy snake's body for simulation
    std::vector<std::pair<int, int>> body_copy = snake.get_body();
    if (body_copy.empty()) return; // Prevent crashes

    collision = false;

    // Simulate the move
    std::pair<int, int> new_head = body_copy.front();
    if (move == 'R') new_head.first += 1;
    else if (move == 'L') new_head.first -= 1;
    else if (move == 'U') new_head.second += 1;
    else if (move == 'D') new_head.second -= 1;

    // Shift body parts
    std::pair<int, int> prev = new_head;
    for (size_t i = 1; i < body_copy.size(); i++)
    {
        std::swap(prev, body_copy[i]);
    }

    // Check for self-collision
    for (size_t i = 1; i < body_copy.size(); i++)
    {
        if (new_head == body_copy[i])
        {
            collision = true;
            break;
        }
    }
}

void Computer::crude_correction()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0, 1);

    int counter = 0;
    while (collision && counter < 25)
    {
        // Choose a random new move
        double take = dist(gen);
        if (take <= 0.25) move = 'R';
        else if (take <= 0.5) move = 'L';
        else if (take <= 0.75) move = 'U';
        else move = 'D';

        self_collision();
        counter++;
    }

    // If still colliding after 25 attempts, force a move
    if (collision)
    {
        std::vector<char> safe_moves = {'R', 'L', 'U', 'D'};
        move = safe_moves[rand() % 4];
    }
}
