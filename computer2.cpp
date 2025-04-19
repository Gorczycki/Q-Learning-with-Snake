//contains crude decision function

#include "computer2.h"


Computer::Computer(Snake& s, Apple& a) : snake(s), apple(a)
{
    direction = 'R';
    collision = false;  
};


//introduce a heuristic to being crowding/folding the snake as in human games, with leaving a cell on the
//ends to allow escape. f(x) represents minimizing distance from snake head to snake tail,
//g(x) represents minimizing area of the snake, as in we imagine filled in cells to create a rectangle around the
//snake's width and height. g(x) may also need to handle avoiding self-collisions and wall-collisions


void Computer::decision()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0,1);
    double give = dist(gen); //for random move occurring x% of the time
    double give2 = dist(gen); //for choosing between random move and determined move
    

    //if(give2 >= epsilon)
    //{
    //if(give <= 0.25)
    //    direction = 'R';
    //else if(give > 0.25 && give <= 0.5)
    //    direction = 'L';
    //else if(give > 0.5 && give <= 0.75)
    //    direction = 'U';
    //else if(give > 0.75)
    //    direction = 'D';
    //}
    //else
    //{
        //pre-computes best move by reduced distance, then sends this best move
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
           
        if(snake.direction == 'R')
        {
            std::vector<double> temp = {radius_1, radius_3, radius_4};
            sort(temp.begin(), temp.end());
            choice = temp[0];

            for(auto b : matches)
            {
                if(b.second == choice)
                {
                    if(self_collision(b.first) == true)
                    {
                        //need to re-calc choice
                        auto it = std::find(temp.begin(), temp.end(), b.second);
                        if(it != temp.end())
                            temp.erase(it);
                        if(temp.empty() == false)
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

            for(auto b : matches)
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

            for(auto b : matches)
            {
                if(b.second == choice)
                {
                    if(self_collision(b.first) == true)
                    {
                        //need to re-calc choice
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

            for(auto b : matches)
            {
                if(b.second == choice)
                {
                    if(self_collision(b.first) == true)
                    {
                        //need to re-calc choice
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





//main function
void Computer::chooseAction(State state)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> explore(0,1);
    std::vector<char> possible_actions = {'R','L','U','D'};

    if(explore(gen) < epsilon)
    {
        //std::uniform_int_distribution<int> action_dist(0,3);
        //return possible_actions[action_dist(gen)];
        decision(); //deterministic
    }
    else
    {
        auto& actions = Q_table[state];
        if(actions.empty())
        {   
            std::uniform_int_distribution<int> action_dist(0,3);
            move = possible_actions[action_dist(gen)];
        }
        else
        {
            char best_action = 'R';
            float max_q = -1e9;
            for(const auto& [action, q_value] : actions)
            {
                if(q_value > max_q)
                {
                    max_q = q_value;
                    best_action = action;
                }
            }
            move = best_action;
        }
    }
}



//void Computer::updateQ(State state, char action, float reward, State next_state)
//{
//    float q_predict = Q_table[state][action];
//    float q_target = reward;
//
//    //only add future reward if next_state is not terminal
//    if(!self_collision(action))
//    {
//        auto& next_actions = Q_table[next_state];
//        if(!next_actions.empty())
//        {
//            float max_next_q = -1e9;
//            for(const auto& [next_action, next_q] : next_actions)
//                if(next_q > max_next_q)
//                    max_next_q = next_q;
//            q_target += gamma * max_next_q;
//        }
//    }
//
//    Q_table[state][action] = (1 - alpha) * q_predict + alpha * q_target;
//}



bool operator<(const Computer::State& lhs, const Computer::State& rhs)
{
    return std::tie(lhs.dx, lhs.dy, lhs.current_dir,
                    lhs.danger_ahead, lhs.danger_left, lhs.danger_right,
                    lhs.danger_up, lhs.danger_down)
         < std::tie(rhs.dx, rhs.dy, rhs.current_dir,
                    rhs.danger_ahead, rhs.danger_left, rhs.danger_right,
                    rhs.danger_up, rhs.danger_down);
}









//if crude decision lead to self or wall collision in a certain state space last game,
//reduce probability of crude decision being chosen again in this game, instead higher weighting on long-term
//move choice

