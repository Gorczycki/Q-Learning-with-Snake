#include "computer.h"
#include <cmath>

Computer::Computer(Snake& s, Apple& a) : snake(s), apple(a)
{
    weights = {0.1, -0.1, -0.1, 0.1, -0.1};
    features = {1,1,1,1,1};
    prev_head = snake.get_head();
};


void Computer::move_generator()
{
    int wall_x = 16;
    int wall_y = 14;
    std::pair<int, int> curr_head = snake.get_head();

    double old_distance = sqrt(pow(prev_head.first - apple.get_apple_loc().first, 2) +
                               pow(prev_head.second - apple.get_apple_loc().second, 2));

    double new_distance = sqrt(pow(curr_head.first - apple.get_apple_loc().first, 2) +
                               pow(curr_head.second - apple.get_apple_loc().second, 2));


    distance = sqrt(pow(snake.get_head().first - apple.get_apple_loc().first, 2) + 
    pow(snake.get_head().second - apple.get_apple_loc().second,2));

    features[0] = distance;

    //features[0] = std::abs(snake.get_head().first - apple.get_apple_loc().first);
    //features[1] = std::abs(snake.get_head().second - apple.get_apple_loc().second);


    double reward = -0.1;

    if(snake.get_head().first+1 == wall_x) //right
        features[1] = 1;
    else
        features[1] = 0;
    if(snake.get_head().first-1 == 0) //left
        features[2] = 1;
    else
        features[2] = 0;
    if(snake.get_head().second+1 == wall_y)
        features[3] = 1;
    else
        features[3] = 0;
    if(snake.get_head().second - 1 == 0)
        features[4] = 1;
    else
        features[4] = 0;


    if (curr_head == apple.get_apple_loc())
        reward = 10.0;  
    else if (snake.get_head().first == 16 || snake.get_head().first == -1 ||
    snake.get_head().second == -1 || snake.get_head().second == 16) 
        reward = -20.0;
    else if(new_distance < old_distance)
        reward = 1.0;  
    else
       reward = -0.5;  // Small penalty for moving away

    episode_rewards.push_back(reward);
    prev_head = curr_head;

    //computing Q_values:
    std::vector<std::vector<double>> action_features(4, std::vector<double>(features.size()));
    std::vector<double> q_values(4);

    for (int a = 0; a < 4; a++)
    {

        action_features[a] = features;

        switch (a)
        {
            case 0: // Moving Right
                action_features[a][0] = std::abs(snake.get_head().first + 1 - apple.get_apple_loc().first);
                action_features[a][1] = std::abs(snake.get_head().second - apple.get_apple_loc().second);
                action_features[a][2] = (snake.get_head().first + 2 == wall_x) ? 1 : 0;
                break;
            case 1: // Moving Left
                action_features[a][0] = std::abs(snake.get_head().first - 1 - apple.get_apple_loc().first);
                action_features[a][1] = std::abs(snake.get_head().second - apple.get_apple_loc().second);
                action_features[a][3] = (snake.get_head().first - 2 == 0) ? 1 : 0;
                break;
            case 2: // Moving Up
                action_features[a][0] = std::abs(snake.get_head().first - apple.get_apple_loc().first);
                action_features[a][1] = std::abs(snake.get_head().second - 1 - apple.get_apple_loc().second);
                action_features[a][4] = (snake.get_head().second - 2 == 0) ? 1 : 0;
                break;
            case 3: // Moving Down
                action_features[a][0] = std::abs(snake.get_head().first - apple.get_apple_loc().first);
                action_features[a][1] = std::abs(snake.get_head().second + 1 - apple.get_apple_loc().second);
                action_features[a][4] = (snake.get_head().second + 2 == wall_y) ? 1 : 0;
                break;
        }

        q_values[a] = 0.0;
        for (int i = 0; i < action_features[a].size(); i++)
        {
            q_values[a] += weights[i] * action_features[a][i];
        }
    }

    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0,1);
    double give = dist(gen);

    if(give > epsilon)
    {
        //converting to 1,2,3,4 for RLUD
        int best_action = std::distance(q_values.begin(), std::max_element(q_values.begin(), q_values.end()));

        move = (best_action == 0) ? 'R' : 
       (best_action == 1) ? 'L' : 
       (best_action == 2) ? 'U' : 'D';
    }
    else
    {
        std::vector<char> moves = {'R','L','U','D'};
        std::uniform_int_distribution<int> action_dist(0, 3);
        move = moves[action_dist(gen)];
    }

    //recording state-action pair:
    episode_states_actions.push_back({features, move});
    epsilon = std::max(0.1, epsilon - 0.01);
}

void Computer::weight_update()
{
    double G = 0.0;
    for(int t = episode_rewards.size() - 1; t>=0; --t)
    {
        G = gamma * G + episode_rewards[t];
    }

    for (auto& state_action : episode_states_actions) 
    {
        std::vector<double> state = state_action.first;
        char action = state_action.second;

        // Calculate Q(s, a) using weights
        double Q_s_a = 0.0;
        for (int i = 0; i < state.size(); ++i) {
            Q_s_a += weights[i] * state[i];
        }

        // Update weights using the Monte Carlo method
        for (int i = 0; i < state.size(); ++i) {
            weights[i] += alpha * (G - Q_s_a) * state[i];
        }
    }
    alpha = std::max(0.1, alpha - 0.05);
    episode_rewards.clear();
    epsilon = 0.85;
}

