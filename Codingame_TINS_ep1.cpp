#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//link para exercício https://www.codingame.com/ide/puzzle/there-is-no-spoon-episode-1

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/

int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();

    char** grid = new char*[height]; //y - axis
    for (int i = 0; i < height; i++)
    {
        grid[i] = new char[width]; //x - axis
    }
    
    cerr<< "Tamanhos: " <<width<<" "<<height<<endl;
    string line;
    for (int i = 0; i < height; i++) 
    {
        getline(cin, line); 
        cerr<<line<<endl;
        line.copy(grid[i], width, 0);
    }
    cerr<<"grid[0][0] = "<<grid[0][0]<<" | grid[0][1] = "<<grid[0][1]<<endl;
    cerr<<"grid[1][0] = "<<grid[1][0]<<" | grid[1][1] = "<<grid[1][1]<<endl;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int output[6];
            output [0] = j;
            output [1] = i;

            //search em x axis
            for (int k = j+1; k <= width; k++)
            {

                   
                if (grid[i][k] == 48) // 48 is ascii for 0
                {
                    output[2] = k;
                    output[3] = i;
                    break;
                }else 
                {
                output[2] = -1;
                output[3] = -1;
                }
            }
            
            //search in y axis
            for (int k = i+1; k <= height; k++)
            {
                
                if (grid[k][j] == 48) // 48 is ascii for 0
                {
                    output[4] = j;
                    output[5] = k;
                    break;
                }else 
                {
                output[4] = -1;
                output[5] = -1;
                }
            }

            cout<<output[0]<<" "<<output[1]<<" "<<output[2]<<" "<<output[3]<<" "<<output[4]<<" "<<output[5]<<endl;

        }
    }

}
