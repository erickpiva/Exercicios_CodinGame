#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <list>

using namespace std;

struct node
{ 
    int X;                          //X Coord
    int Y;                          //Y Coord
    bool bIsVisited;                //Have we calculate from this cell yet?
    bool bIsObstacle;               //Is this cell a Obstacle (# in the string input)
    node* Parent;                   //From what cell did we calculate the best output
    vector<node*> vNeighbour;       //What are the neighbour from this cell (is a grid, so anywhing from the four sides)
    float fLocalScore;              //Local parameter to the a* algorithm
    float fGlobalScore;             //Globar parameter (defined as a line distance)

    bool operator<(node* a)
    {
        if (this->fGlobalScore < a->fGlobalScore)
        {
            return true;
        }
        return false;
    }

};

float HeuristicDistance (const node* a, const node* b)
{
    int X = abs(a->X - b->X);
    int Y = abs(a->Y - b->Y);

    return sqrt(X*X + Y*Y);
}

void SetToKnownState(node a[], const int Rows, const int Columns)
{
    for (int y = 0; y < Rows; ++y)
        for (int x = 0; x < Columns; ++x)
        {
            a[y*Columns + x].X = x;
            a[y*Columns + x].Y = y;
            a[y*Columns + x].bIsObstacle = true;
            a[y*Columns + x].bIsVisited = false;
            a[y*Columns + x].Parent = nullptr;
            a[y*Columns + x].fLocalScore = INFINITY;
            a[y*Columns + x].fGlobalScore = INFINITY;
            
        }
    
}

void SetObstacles(node a[], int Rows, int Columns, string s[])
{
    for (int y = 0; y < Rows; ++y)
        {
            for (int x = 0; x < Columns; ++x)
                {
                    if (s[y][x] == 'T' || s[y][x] == '.' || s[y][x] == 'C')
                    {
                        a[y*Columns + x].bIsObstacle = false;
                    }
                }
        }
}


void SolvePath (node array[], int Rows, int Columns,string map[], node* Start, node* End, list<int> &output_path)
{
    cerr<<"A*Called"<<endl;
    output_path.clear();
    SetToKnownState(array, Rows, Columns);
    SetObstacles(array, Rows, Columns, map);
    
    
        node* CurrentNode = Start;
        CurrentNode->fLocalScore = 0.0;
        CurrentNode->fGlobalScore = HeuristicDistance(CurrentNode, End);
        list<node*> CellsToVisit;

        CellsToVisit.push_back(Start);

        while(!CellsToVisit.empty())
        {    
            //Sort in ascendind order of Global Score thanks to the < overload
            CellsToVisit.sort();
            //pop all the fronts that is visited 
            while(!CellsToVisit.empty() && CellsToVisit.front()->bIsVisited == true)
            {
                CellsToVisit.pop_front();
            }
            //if list gets all popped, break the loop
            if (CellsToVisit.empty())
            {
                break;
            }
            CurrentNode = CellsToVisit.front();
            CurrentNode->bIsVisited = true;

            for (int i = 0; i < CurrentNode->vNeighbour.size(); ++i)
            {
                if (!CurrentNode->vNeighbour[i]->bIsVisited && !CurrentNode->vNeighbour[i]->bIsObstacle)
                {
                    CellsToVisit.push_back(CurrentNode->vNeighbour[i]);
                }

                float fPossiblylocalScore = CurrentNode->fLocalScore+HeuristicDistance(CurrentNode,CurrentNode->vNeighbour[i]);

                if (fPossiblylocalScore < CurrentNode->vNeighbour[i]->fLocalScore)
                {
                    CurrentNode->vNeighbour[i]->Parent = CurrentNode;
                    CurrentNode->vNeighbour[i]->fLocalScore = fPossiblylocalScore;
                    CurrentNode->vNeighbour[i]->fGlobalScore = CurrentNode->vNeighbour[i]->fLocalScore + HeuristicDistance(CurrentNode->vNeighbour[i], End);
                }

            }

        }

        //Pathmaking (It makes a reverse path)
        node* temp = End;
        while(temp->Parent != nullptr)
        {
            if (temp->Parent->X > temp->X)
            {
                output_path.push_back(3); //Go left
                cerr<<"LEFT"<<endl;
            }
            if (temp->Parent->X < temp->X)
            {
                output_path.push_back(4); //Go right
                cerr<<"RIGHT"<<endl;
            }
            if (temp->Parent->Y < temp->Y)
            {
                output_path.push_back(2);//Go Down
                cerr<<"DOWN"<<endl;
            }
            if (temp->Parent->Y > temp->Y)
            {
                output_path.push_back(1); //Go Up
                cerr<<"UP"<<endl;
            }
            temp = temp->Parent;
        }
            
}


int main()
{
    int R; // number of rows.
    int C; // number of columns.
    int A; // number of rounds between the time the alarm countdown is activated and the time the alarm goes off.
    cin >> R >> C >> A; cin.ignore();

    string output[5] = {"WRONG","UP", "DOWN", "LEFT", "RIGHT"};
    
    //Creating the maze grid and conection (it will check for obstacles latter)
    node* Maze = new node[R*C];
    SetToKnownState(Maze, R, C);
    for (int y = 0; y < R; ++y)
        for (int x = 0; x < C; ++x)
        {
            if (y != 0) //NorthConecction
            {
                Maze[y*C + x].vNeighbour.push_back(&Maze[(y - 1)*C + (x + 0)]);
            }
            if (y != R-1)//SouthConecction0
            {
                Maze[y*C + x].vNeighbour.push_back(&Maze[(y + 1)*C + (x + 0)]);
            }
            if (x != 0)//WestConecction
            {
                Maze[y*C + x].vNeighbour.push_back(&Maze[(y - 0)*C + (x - 1)]);
            }
            if (x != C-1)//EastConecction
            {
                Maze[y*C + x].vNeighbour.push_back(&Maze[(y - 0)*C + (x + 1)]);
            }
        }
    
    

    int nKR;                   // row where Kirk is located.
    int nCR = R;                   //row where Control Room is located. R is a placeholder
    int nKC;                   // column where Kirk is located.
    int nCC = C;                   //column where control romm is located. C is a placeholder
    bool bLookingForControlRoom = true; 
    bool bIsControlRoomFound = false; 
    bool bGoingBackToTerminal = false;
    bool bBehaviorChangeTurn = true;
    bool bControlRoomFoundYet = false; 
    
        
    list<int> HomeDirection;             //Indexes the output
   
        
    while (1) {
              
        cin >> nKR >> nKC;
        cin.ignore();
        
        string *sROW = new string[R]; // C of the characters in '#.TC?' (i.e. one line of the ASCII maze).
        for (int y = 0; y < R; ++y) 
        {            
            cin >> sROW[y]; cin.ignore();
            if (!bControlRoomFoundYet)    
            {   
                for(int x = 0; x < C; ++x)
                {
                    if(sROW[y][x] == 'C') // looking for Control Room
                    {   
                        nCR = y;
                        nCC = x;
                        bIsControlRoomFound = true;
                        bLookingForControlRoom = false;
                        bBehaviorChangeTurn = true;
                    }
                }     
                
            }
            
        }
        SetObstacles(Maze, R, C, sROW); //Set the obtacles to calculate distance um bLookingForControlRoom
        if (nKR == nCR && nKC == nCC)   //This is only posible after C is found and nCR and nCC is updated. 
        {
            bGoingBackToTerminal = true;
            bIsControlRoomFound = false;
            bBehaviorChangeTurn = true;
        }
        //Debug
        
        cerr<<"LFCR "<<bLookingForControlRoom<<" ICRF "<<bIsControlRoomFound<<" GBTT "<<bGoingBackToTerminal<<endl;
        
        //We'll need three distinct behaviour
                
        if (bLookingForControlRoom)
        {
            if (bBehaviorChangeTurn)
            {
                HomeDirection.clear();
                bBehaviorChangeTurn = false;
            }
            if(HomeDirection.empty())
            {
                node* CurrentNode = &Maze[nKR*C + nKC];
                node* EndNode = nullptr;
                float tempDistance = 0.0f;
                for (int y = 0; y < R; ++y)
                    for (int x = 0; x < C; ++x)
                    {
                        if(!Maze[y*C+x].bIsObstacle)
                        {
                            float distance = HeuristicDistance(CurrentNode, &Maze[y*C+x]);
                            if (distance > tempDistance)
                            {
                                tempDistance = distance;
                                EndNode = &Maze[y*C+x];
                            }
                        }
                    }
                cerr<<CurrentNode->X<<"."<<CurrentNode->Y<<" "<<EndNode->X<<"."<<EndNode->Y<<endl;
                SolvePath(Maze, R, C, sROW, CurrentNode, EndNode, HomeDirection);
                
            }

            if (!HomeDirection.empty())
            {        
                cout<<output[HomeDirection.front()]<<endl;
                HomeDirection.pop_front();
            }                         
            
        }

        

        if (bIsControlRoomFound)
        {
            if (bBehaviorChangeTurn)
            {
                HomeDirection.clear();
                bBehaviorChangeTurn = false;
            }

            if(HomeDirection.empty())
            {         
                node* CurrentNode = &Maze[nKR*C+nKC];
                node* ControlRoom = &Maze[nCR*C+nCC];
                cerr<<CurrentNode->X<<"."<<CurrentNode->Y<<" "<<ControlRoom->X<<"."<<ControlRoom->Y<<endl;
                SolvePath(Maze, R, C, sROW, CurrentNode, ControlRoom, HomeDirection);
                bControlRoomFoundYet = true;
            }

            if(!HomeDirection.empty())
            {
                cout<<output[HomeDirection.front()]<<endl;
                HomeDirection.pop_front();
                
            }


        }

        
        if (bGoingBackToTerminal)
        {
            if (bBehaviorChangeTurn)
            {
                HomeDirection.clear();
                bBehaviorChangeTurn = false;
            }

            if (HomeDirection.empty())
            {
                node* CurrentNode = &Maze[nKR*C + nKC];
                node* TerminalNode = nullptr;
                for (int y = 0; y < R; ++y)
                {
                    for (int x = 0; x < C; ++x)
                    {
                        if (sROW[y][x] == 'T')
                        {
                            TerminalNode = &Maze[y*C+x];
                            break;
                        }
                    }
                    if(TerminalNode != nullptr)
                    {
                        break;
                    }
                }
                cerr<<CurrentNode->X<<"."<<CurrentNode->Y<<" "<<TerminalNode->X<<"."<<TerminalNode->Y<<endl;
                SolvePath(Maze, R, C, sROW, CurrentNode, TerminalNode, HomeDirection);
            }

            if(!HomeDirection.empty())
            {
                cout<<output[HomeDirection.front()]<<endl;
                HomeDirection.pop_front();  
            }

        }
        
        delete[] sROW;
        
    }
}
