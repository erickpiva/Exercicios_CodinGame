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

    for (int i = 0; i < lightCount; i++)
    {
        int distance;
        int duration;
        cin >> distance >> duration;
        cin.ignore();

        bool speed_ok = false;

        while (!speed_ok)
        {

            double time_to_travel = (distance / (speed / 3.6));
            int cycle = time_to_travel/duration; // Checks in which cycle the light is when arrives.

            cycle % 2 == 0 ? speed_ok = 1 : speed_ok = 0; // if the integer part of the cycle is even, then it is green.

            if (!speed_ok)
            {
                speed--;
            }
        }
    }

    cout << speed << endl;
}
