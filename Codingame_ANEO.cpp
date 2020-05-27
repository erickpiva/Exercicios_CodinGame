#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
/* Exemplo de input

50
1
200 15

Deve retornar 50 como resposta */


int main()
{
    int speed;
    cin >> speed; cin.ignore();
    int lightCount;
    cin >> lightCount; cin.ignore();
    

    for (int i = 0; i < lightCount; i++) {
        int distance;
        int duration;
        cin >> distance >> duration; cin.ignore();
        
        bool speed_ok = false;
        
        while (!speed_ok){
            
            double time_to_travel = ((double)distance/((double)speed/3.6f));
            for (int n = 0; time_to_travel >= n*duration; n += 2){
                time_to_travel <= (n+1)*duration ? speed_ok = true : speed_ok = false;
                cerr<<n<<" "<<(n+1)<<endl;
                cerr<<distance<<" "<<duration<<" "<<speed<<endl;
                cerr<<time_to_travel<<endl;
            }
            if (!speed_ok){
                speed--;
            }
        }
        
    }

    
    cout << speed << endl;
}
