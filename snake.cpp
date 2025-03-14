#include "snake.h"

Snake::Snake() : direction('R')
{
    //body.push_back({5,8});
    //body.push_back({5,7});
    //body.push_back({4,7});
    //body.push_back({3,7});   

    body.push_back({5,7});
    body.push_back({4,7});
    body.push_back({3,7});
}


//in this manner, snake_grow() is independent of direction, as direction is not called
void Snake::snake_grow()
{
    if(body[body.size()-1].first == body[body.size()-2].first + 1) // direction is 'L'?
        body.push_back({body.back().first - 1, body.back().second});
    else if(body[body.size()-1].first == body[body.size()-2].first - 1) // 'R'
        body.push_back({body.back().first - 1, body.back().second});
    else if(body[body.size()-1].second == body[body.size()-2].second + 1) // 'U'?
        body.push_back({body.back().first, body.back().second + 1});
    else if(body[body.size()-1].second == body[body.size()-2].second - 1) // 'D'?
        body.push_back({body.back().first, body.back().second - 1});

}


//snake may change direction before entire snake has adjusted for the most recent
//direction change

//therefore we will need a bool check in the for loop

//actually not true? we can only increment snake once every time, when the time_update
//function returns true. Therefore, direction changes will onyl happen between consecutive time updates
//where-as in actual snake, we can spam direction change. so is the shift called by direction change,
//or direction change is prompted by a shift?



//dependent on direction, so we cant do a simple for-loop shift of all elements as shown below for 'L'
void Snake::shift_snake()
{
    if(snake_get_direction() == 'R')
    {
        std::pair<int, int> temp = body.front();
        std::pair<int, int> temp2;
        body.front().first = body.front().first + 1;
        for(int i = 1; i<body.size(); i++)
        {
            temp2 = body[i];
            body[i] = temp;
            temp = temp2;
        }
    }
    else if(snake_get_direction() == 'L')
    {
        std::pair<int, int> temp = body.front();
        std::pair<int, int> temp2;
        body.front().first = body.front().first - 1;
        for(int i = 1; i<body.size(); i++)
        {
            temp2 = body[i];
            body[i] = temp;
            temp = temp2;
        }
    }
    else if(direction == 'U')
    {
        std::pair<int, int> temp = body.front();
        std::pair<int, int> temp2;
        body.front().second = body.front().second + 1;
        for(int i = 1; i<body.size(); i++)
        {
            temp2 = body[i];
            body[i] = temp;
            temp = temp2;
        }
    }
    else if(direction == 'D')
    {
        std::pair<int, int> temp = body.front();
        std::pair<int, int> temp2;
        body.front().second = body.front().second - 1;
        for(int i = 1; i<body.size(); i++)
        {
            temp2 = body[i];
            body[i] = temp;
            temp = temp2;
        }
    }
}

std::vector<std::pair<int, int>> Snake::get_body()
{
    return body;
}

char Snake::snake_get_direction()
{
    return direction;
}

std::pair<int, int> Snake::get_head()
{
    return body.front();
}