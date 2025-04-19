#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    ofstream file("game_frames.txt", ios::trunc);
    if(!file.is_open())
    {
        cerr<<"failed to open"<<endl;
        return 1;
    }
    else
        cout<<"cleared"<<endl;
    






    return 0;
}