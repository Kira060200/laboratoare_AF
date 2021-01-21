#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
ifstream f("graf.in");
ofstream g("graf.out");
int n,m;
int **mat;
vector<int> lin;
vector<int> col;
int nr=0;
void citire()
{
    f>>n>>m;
    mat = new int*[n];
    for(int i=0; i<n; i++)
        mat[i] = new int[m];
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            {
                f>>mat[i][j];
                if(mat[i][j])
                {
                    mat[i][j]=0;
                    lin.push_back(i);
                    col.push_back(j);
                    nr++;
                }
            }
}
void af()
{
    for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
                cout<<mat[i][j]<< ' ';
            cout<<endl;
        }
}
//To store matrix cell cordinates
struct Point
{
    int x;
    int y;
};

// A Data Structure for queue used in BFS
struct queueNode
{
    Point pt;  // The cordinates of a cell
    int dist;  // cell's distance of from the source
};

// check whether given cell (row, col) is a valid
// cell or not.
bool isValid(int row, int col)
{
    // return true if row number and column number
    // is in range
    return (row >= 0) && (row < n) &&
           (col >= 0) && (col < m);
}

// These arrays are used to get row and column
// numbers of 4 neighbours of a given cell
int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};

// function to find the shortest path between
// a given source cell to a destination cell.
int BFS(Point src, Point dest)
{

    bool visited[n][m];
    memset(visited, false, sizeof visited);

    // Mark the source cell as visited
    visited[src.x][src.y] = true;

    // Create a queue for BFS
    queue<queueNode> q;

    // Distance of source cell is 0
    queueNode s = {src, 0};
    q.push(s);  // Enqueue source cell

    // Do a BFS starting from source cell
    while (!q.empty())
    {
        queueNode curr = q.front();
        Point pt = curr.pt;
        //cout<<pt.x<< ' '<<pt.y<<endl;
        // If we have reached the destination cell,
        // we are done
        if (pt.x == dest.x && pt.y == dest.y)
            return curr.dist;

        // Otherwise dequeue the front
        // cell in the queue
        // and enqueue its adjacent cells
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            // if adjacent cell is valid, has path and
            // not visited yet, enqueue it.
            if (isValid(row, col) && !mat[row][col] &&
               !visited[row][col])
            {
                // mark cell as visited and enqueue it
                visited[row][col] = true;
                queueNode Adjcell = { {row, col},
                                      curr.dist + 1 };
                q.push(Adjcell);
            }
        }
    }

    // Return -1 if destination cannot be reached
    return -1;
}

// Driver program to test above function
int main()
{
    citire();
    //af();

    int source_lin, source_col;
    while(f>>source_lin>>source_col)
    {
        Point source = {source_lin-1, source_col-1};
        int mini = m*n;
        Point saved;
        for(int i=0;i<nr;i++)
            {
                Point dest = {lin[i], col[i]};
                int dist = BFS(source, dest);
                if (dist < mini)
                    {
                        mini = dist;
                        saved = dest;
                    }
            }
        if (mini != n*m)
            g << mini << " [" << saved.x+1 << ", " << saved.y+1 <<"]"<<endl;
        else
            cout << "Shortest Path doesn't exist";
    }
    return 0;
}
