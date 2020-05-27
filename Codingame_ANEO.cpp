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

            double time_to_travel = ((double)distance / ((double)speed / 3.6f));
            for (int n = 0; time_to_travel >= n * duration; n += 2)
            {
                float end_of_time = (n + 1) * duration;
                time_to_travel <= end_of_time ? speed_ok = true : speed_ok = false;
                cerr << "Round " << n * duration << " " << (n + 1) * duration << endl;
                cerr << "Dist " << distance << " Dur " << duration << " Speed " << speed << endl;
                cerr << "tempo pra chegar " << time_to_travel << endl;
            }
            if (!speed_ok)
            {
                speed--;
            }
        }
    }

    cout << speed << endl;
}
