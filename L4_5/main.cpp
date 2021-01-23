#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
#include <climits>
#include <queue>

using namespace std;

ifstream f ("grafpond.in");
int n, m;
int** w;
int** p;
int** d;
bool negative_cycle = false;
void read ()
{
    int x, y, z;
    f >> n >> m;

    d = new int*[n];
    p = new int*[n];
    w = new int*[n];

    for (int i = 0; i < n; ++i)
    {
        d[i] = new int[n];
        p[i] = new int[n];
        w[i] = new int[n];
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            if (i != j)
                w[i][j] = INT_MAX;
            else
                w[i][j] = 0;
        }

    for (int i = 0; i < m; ++i)
    {
        f >> x >> y >> z;
        w[--x][--y] = z;
    }
}

void floyd ()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
        {
            if (w[i][j] == INT_MAX)
                p[i][j] = -1;
            else
                p[i][j] = i;

            if (i != j)
                d[i][j] = w[i][j];
            else
                d[i][j] = 0;
        }
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if (d[i][k]!=INT_MAX && d[k][j]!=INT_MAX && d[i][j] > d[i][k] + d[k][j])
                    {
                        d[i][j] = d[i][k] + d[k][j];
                        p[i][j] = p[k][j];
                    }
    for (int i = 0; i < n; i++)
        if (d[i][i] < 0)
        {
            negative_cycle = true;
            break;
        }
}

void road(int i, int j)
{
    if(i!=j)
        road(i,p[i][j]);
    cout<<j<< ' ';
}
int main()
{

    read ();

    floyd ();

    if (negative_cycle)
    {
        cout << "\nGraful contine circuit de cost negativ:\n";
        for (int i = 0; i < n; ++i)
            if(d[i][i]<0)
                cout<<i+1<<' ';
        cout<<endl;
    }
    else
    {
        for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                    cout<<d[i][j]<<' ';
                cout<<endl;
            }
    }

    return 0;
}
