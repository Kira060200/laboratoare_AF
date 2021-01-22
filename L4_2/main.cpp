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
int *d, *tata;
int n, m;
int k;
int *pct_control;
int start;
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
        adj[y].push_back (pair<int, int> (x, z) );//pt ca e neorientat in cerinta
    }

    cout<<"Nr pct control: ";
    cin>>k;

    cout<<endl<<"Pct control: ";
    pct_control = new int[k];
    for(int i=0;i<k;++i)
        cin>>pct_control[i];

    cout<<endl<<"Varf start: ";
    cin>>start;
    --start;
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
    for (int i = 0; i < n; ++i)
        cout << tata[i] << ' ';

    cout << '\n';
    int mini = INT_MAX;
    int pct;
    for (int i = 0; i < k; ++i)
        if(d[pct_control[i]-1]<mini)
            {
                mini = d[pct_control[i]-1];
                pct=pct_control[i]-1;
            }

    cout <<"Distanta: "<<mini<< '\n';
    if (tata[pct] != -1)
    {
        while (tata[pct] != -1)
        {
            cout << pct + 1 << ' ';
            pct = tata[pct];
        }
        cout << pct + 1 << ' ';
    }
    else
    {
        cout << "Unreachable node.\n";
    }
}

int main()
{

    read();
    dijkstra ();
    print();

    delete[] tata;
    delete[] d;

    return 0;
}
