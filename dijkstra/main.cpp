#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
#include <climits>
#include <queue>

using namespace std;

ifstream f ("dijkstra.in");
ofstream g ("dijkstra.out");
int *d, *tata;
int n, m;
int start=0;
vector<vector<pair<int, int>>> adj;

void read ()
{
    int x, y, z;
    f >> n >> m;

    for (int i = 0; i < n; ++i)
    {
        vector<pair<int, int>> v;
        adj.push_back (v);
    }

    for (int i = 0; i < m; ++i)
    {
        f >> x >> y >> z;
        adj[--x].push_back (pair<int, int> (--y, z) );
    }
}

void init()
{
    tata = new int[n];
    d = new int[n];

    for (int i = 0; i < n; ++i)
    {
        tata[i] = -1;
        d[i]=INT_MAX;
    }
}

void dijkstra ()
{
    priority_queue<pair<int, int>> pq;
    vector<bool> selected (n, false);

    init ();

    d[start] = 0;
    pq.push (pair<int, int> (start, d[start]) );

    while (!pq.empty() )
    {
        int u = pq.top().first;
        pq.pop();
        selected[u] = true;

        for (int i = 0; i < adj[u].size(); ++i)
        {
            int v = adj[u][i].first;
            int weight = adj[u][i].second;

            if (d[u] + weight < d[v])
            {
                d[v] =  d[u] + weight;
                tata[v] = u;

                pq.push (pair<int, int> (v, d[v]) );
            }
        }
    }
}

void print()
{
    for (int i = 1; i < n; ++i)
        if(d[i]==INT_MAX)
            g << 0 << ' ';
        else g << d[i] << ' ';
    g.close();
}

int main()
{

    read();
    dijkstra ();
    print();

    return 0;
}
