#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int speed;
    cin >> speed;
    cin.ignore();
    int lightCount;
    cin >> lightCount;
    cin.ignore();

    vector<int> distance;
    vector<int> duration;

    for (int i = 0; i < lightCount; i++)
    {
        int temp_distance;
        int temp_duration;
        cin >> temp_distance >> temp_duration;
        distance.push_back(temp_distance);
        duration.push_back(temp_duration);
    }

    bool speed_ok = false; //flag to check if the actual speed works

    for (int i = 0; i < lightCount; i++)
    {
        double time_to_travel = (distance[i] / (speed / 3.6));
        int cycle = time_to_travel / duration[i];
        cycle % 2 == 0 ? speed_ok = 1 : speed_ok = 0;

        if (!speed_ok)
        {
            speed--;
            i = 0;
        }
    }

        cout << speed << endl;
}
