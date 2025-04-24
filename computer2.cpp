//contains crude decision function

#include "computer2.h"


Computer::Computer(Snake& s, Apple& a) : snake(s), apple(a)
{
    //direction = 'R';
    //collision = false;  
    loadQTable("qtable.dat");
};


//introduce a heuristic to being crowding/folding the snake as in human games, with leaving a cell on the
//ends to allow escape? f(x) represents minimizing distance from snake head to snake tail,
//g(x) represents minimizing area of the snake, as in we imagine filled in cells to create a rectangle around the
//snake's width and height. g(x) may also need to handle avoiding self-collisions and wall-collisions



void Computer::decision()
{   
    snake_head_y = snake.get_body().front().second;
    snake_head_x = snake.get_body().front().first;
    apple_y = apple.get_apple_loc().second;
    apple_x = apple.get_apple_loc().first;
    radius_1 = sqrt( pow((snake_head_x+1) - apple_x, 2) + pow(snake_head_y - apple_y, 2)); //right
    radius_2 = sqrt( pow((snake_head_x-1) - apple_x, 2) + pow(snake_head_y - apple_y, 2)); //left
    radius_3 = sqrt( pow(snake_head_x - apple_x, 2) + pow((snake_head_y+1) - apple_y, 2)); //up
    radius_4 = sqrt( pow(snake_head_x - apple_x, 2) + pow((snake_head_y-1) - apple_y, 2)); //down
    matches['R'] = radius_1;
    matches['L'] = radius_2;
    matches['U'] = radius_3;
    matches['D'] = radius_4;

    std::map<char, int> new_matches;
       
    if(snake.direction == 'R')
    {
        std::vector<double> temp = {radius_1, radius_3, radius_4};
        sort(temp.begin(), temp.end());
        choice = temp[0];

        for(auto const& pair : matches)
            if(pair.first != 'L')
                new_matches[pair.first] = pair.second;

        for(auto b : new_matches)
        {
            if(b.second == choice)
            {
                if(self_collision(b.first) == true)
                {
                    //need to re-calc choice, delete the failing move/radius
                    auto it = std::find(temp.begin(), temp.end(), b.second);
                    if(it != temp.end())
                        temp.erase(it);
                    if(temp.empty() != true)
                    {
                        sort(temp.begin(), temp.end());
                        choice = temp[0];
                    }
                    //else
                        //break, and game_toggle off      
                }
                else if(self_collision(b.first) == false)
                {
                    move = b.first;
                    break;
                }
            }
        }
    }
    else if(snake.direction == 'L')
    {
        std::vector<double> temp = {radius_2, radius_3, radius_4};
        sort(temp.begin(), temp.end());
        choice = temp[0];

        for(auto const& pair : matches)
            if(pair.first != 'R')
                new_matches[pair.first] = pair.second;

        for(auto b : new_matches)
        {
            if(b.second == choice)
            {
                if(self_collision(b.first) == true)
                {
                    //need to re-calc choice, delete the failing move/radius
                    auto it = std::find(temp.begin(), temp.end(), b.second);
                    if(it != temp.end())
                        temp.erase(it);
                    if(temp.empty() != true)
                    {
                        sort(temp.begin(), temp.end());
                        choice = temp[0];
                    }
                    //else
                        //break, and game_toggle off      
                }
                else if(self_collision(b.first) == false)
                {
                    move = b.first;
                    break;
                }
            }
        }
    }
    else if(snake.direction == 'U')
    {
        std::vector<double> temp = {radius_1, radius_2, radius_3};
        sort(temp.begin(), temp.end());
        choice = temp[0];

        for(auto const& pair : matches)
            if(pair.first != 'D')
                new_matches[pair.first] = pair.second;

        for(auto b : new_matches)
        {
            if(b.second == choice)
            {
                if(self_collision(b.first) == true)
                {
                    //need to re-calc choice, delete the failing move/radius
                    auto it = std::find(temp.begin(), temp.end(), b.second);
                    if(it != temp.end())
                        temp.erase(it);
                    if(temp.empty() != true)
                    {
                        sort(temp.begin(), temp.end());
                        choice = temp[0];
                    }
                    //else
                        //break, and game_toggle off      
                }
                else if(self_collision(b.first) == false)
                {
                    move = b.first;
                    break;
                }
            }
        }
    }
    else if(snake.direction == 'D')
    {
        std::vector<double> temp = {radius_1, radius_2, radius_4};
        sort(temp.begin(), temp.end());
        choice = temp[0];

        for(auto const& pair : matches)
            if(pair.first != 'U')
                new_matches[pair.first] = pair.second;

        for(auto b : new_matches)
        {
            if(b.second == choice)
            {
                if(self_collision(b.first) == true)
                {
                    //need to re-calc choice, delete the failing move/radius
                    auto it = std::find(temp.begin(), temp.end(), b.second);
                    if(it != temp.end())
                        temp.erase(it);
                    if(temp.empty() != true)
                    {
                        sort(temp.begin(), temp.end());
                        choice = temp[0];
                    }
                    //else
                        //break, and game_toggle off      
                }
                else if(self_collision(b.first) == false)
                {
                    move = b.first;
                    break;
                }
            }
        }
    }
    matches.clear();
    new_matches.clear();
    getstate();
    prev_state = state;
}







bool Computer::self_collision(char move_)
{
    //make a copy of snake's body and then shift it pre-emptively to see

    std::vector<std::pair<int,int>> body_copy = snake.get_body();

    //Computer::decision();
    
    collision = false;

    if(move_ == 'R')//shifting:
    {
        std::pair<int, int> temp = body_copy.front();
        std::pair<int, int> temp2;
        body_copy.front().first = body_copy.front().first + 1;
        for(int i = 1; i<body_copy.size(); i++)
        {
            temp2 = body_copy[i];
            body_copy[i] = temp;
            temp = temp2;
        }
        for(int i = 1; i<body_copy.size(); i++)
        {
            if(body_copy.front() == body_copy[i])
            {
                collision = true;
                return collision;
            }
        }
    }
    else if(move_ == 'L')
    {
        std::pair<int, int> temp = body_copy.front();
        std::pair<int, int> temp2;
        body_copy.front().first = body_copy.front().first - 1;
        for(int i = 1; i<body_copy.size(); i++)
        {
            temp2 = body_copy[i];
            body_copy[i] = temp;
            temp = temp2;
        }
        for(int i = 1; i<body_copy.size(); i++)
        {
            if(body_copy.front() == body_copy[i])
            {
                collision = true;
                return collision;
            }
        }
    }
    else if(move_ == 'U')
    {
        std::pair<int, int> temp = body_copy.front();
        std::pair<int, int> temp2;
        body_copy.front().second = body_copy.front().second + 1;
        for(int i = 1; i<body_copy.size(); i++)
        {
            temp2 = body_copy[i];
            body_copy[i] = temp;
            temp = temp2;
        }
        for(int i = 1; i<body_copy.size(); i++)
        {
            if(body_copy.front() == body_copy[i])
            {
                collision = true;
                return collision;
            }
        }
    }
    else if(move_ == 'D')
    {
        std::pair<int, int> temp = body_copy.front();
        std::pair<int, int> temp2;
        body_copy.front().second = body_copy.front().second - 1;
        for(int i = 1; i<body_copy.size(); i++)
        {
            temp2 = body_copy[i];
            body_copy[i] = temp;
            temp = temp2;
        }
        for(int i = 1; i<body_copy.size(); i++)
        {
            if(body_copy.front() == body_copy[i])
            {
                collision = true;
                return collision;
            }
        }
    }

    return collision;
}





void Computer::master_move()
{
    getstate(); 
    prev_state = state;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0,1); 
    double give = dist(gen); //for random move occurring x% of the time

    if(give <= epsilon)
        decision();
    else
        q_decision();
}


void Computer::getstate() {
    int dx = (apple_x > snake_head_x) ? 1 : (apple_x < snake_head_x) ? -1 : 0;
    int dy = (apple_y > snake_head_y) ? 1 : (apple_y < snake_head_y) ? -1 : 0;
    
    char dir = snake.direction;
    state = std::make_tuple(
        dx, dy, dir,
        dir != 'L' && self_collision('R'),
        dir != 'R' && self_collision('L'),
        dir != 'D' && self_collision('U'),
        dir != 'U' && self_collision('D')
    );
}


void Computer::q_decision()
{
    getstate();
    prev_state = state;

    double max_q = -std::numeric_limits<double>::infinity();
    char best_move = snake.direction; // fallback in case all options are invalid

    if (Qtable[state].empty()) 
    {
        for (char a : {'R','L','U','D'}) {
            Qtable[state][a] = 1.0;
        }
    }

    for (char a : {'R','L','U','D'})
    {
        // Skip the move that would reverse the snake
        if ((snake.direction == 'R' && a == 'L') ||
            (snake.direction == 'L' && a == 'R') ||
            (snake.direction == 'U' && a == 'D') ||
            (snake.direction == 'D' && a == 'U'))
        {
            continue;
        }

        if (Qtable[state][a] > max_q)
        {
            max_q = Qtable[state][a];
            best_move = a;
        }
    }

    move = best_move;
}



//updateq called immediately after master_move() called
void Computer::updateq()
{
    //State current_state = state;
    getstate();

    float reward = reward_step;
    bool terminal_state = false;


    //self collision
    for(int i = 1; i < snake.get_body().size(); i++) {
        if(snake.get_head() == snake.get_body()[i]) {
            reward = reward_death;
            terminal_state = true;
            break;
        }
    }

    //wall collision:
    if (!terminal_state) {
        if(snake.get_head().first == 16 || snake.get_head().first == -1 ||
           snake.get_head().second == 14 || snake.get_head().second == -1) {
            reward = reward_death;
            terminal_state = true;
        }
    }

    if (!terminal_state && snake.get_head() == apple.get_apple_loc()) {
        reward = reward_apple;
    }

    double max_future_q = 0.0;
    if (!terminal_state) {
        for (char a : {'R', 'L', 'U', 'D'}) {
            max_future_q = std::max(max_future_q, Qtable[state][a]);
        }
    }

    Qtable[prev_state][move] += alpha * (
    reward + gamma * max_future_q - Qtable[prev_state][move]
    );


    if(epsilon > 0.85)
        epsilon *= 0.9995;
}




void Computer::saveQTable(const std::string& filename) {
    std::ofstream outfile(filename);
    for (const auto& state_entry : Qtable) {
        const auto& state = state_entry.first;
        outfile << std::get<0>(state) << " " << std::get<1>(state) << " " 
                << std::get<2>(state) << " " << std::get<3>(state) << " "
                << std::get<4>(state) << " " << std::get<5>(state) << " "
                << std::get<6>(state) << " ";
        
        for (const auto& action_entry : state_entry.second) {
            outfile << action_entry.first << " " << action_entry.second << " ";
        }
        outfile << "\n";
    }
}



void Computer::loadQTable(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile) return;  // No file exists yet
    
    Qtable.clear();  // Clear existing Q-table
    
    std::string line;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int dx, dy;
        char dir;
        bool dr, dl, du, dd;
        iss >> dx >> dy >> dir >> dr >> dl >> du >> dd;
        
        State state = std::make_tuple(dx, dy, dir, dr, dl, du, dd);
        
        char action;
        double q_value;
        while (iss >> action >> q_value) {
            Qtable[state][action] = q_value;
        }
    }
}









//if crude decision lead to self or wall collision in a certain state space last game,
//reduce probability of crude decision being chosen again in this game, instead higher weighting on long-term
//move choice

