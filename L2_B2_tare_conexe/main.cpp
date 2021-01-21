#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <unordered_set>
#include <set>

using namespace std;

ifstream f ("ctc.in");
ofstream g ("ctc.out");
//Kosaraju
void print (int n, int m, vector<vector<int>>& adj)
{
    for (int i = 0; i < n; ++i)
    {
        cout << i + 1 << ": ";
        for (int j = 0; j < adj[i].size(); ++j)
        {
            cout << adj[i][j] + 1 << " ";
        }
        cout << '\n';
    }
}

void read (int& n, int& m, vector<vector<int>>& adj, vector<vector<int>>& adjTrans)
{
    int x, y;
    f >> n >> m;

    for (int i = 0; i < n; ++i)
    {
        vector<int> v;
        adj.push_back (v);
        adjTrans.push_back (v);
    }

    for (int i = 0; i < m; ++i)
    {
        f >> x >> y;
        --x;
        --y;

        adj[x].push_back (y);
        adjTrans[y].push_back (x);
    }
}

void DFS (int u, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& dfsTransOrder)
{
    visited[u] = true;
    for (int i = 0; i < adj[u].size(); ++i)
    {
        int v = adj[u][i];
        if (!visited[v])
        {
            DFS (v, adj, visited, dfsTransOrder);
            dfsTransOrder.push (v);
        }
    }
}
void DFSTransposed (int u, vector<vector<int>>& adj, vector<bool>& visited, vector<int>& component)
{
    visited[u] = true;
    component.push_back (u + 1);
    for (int i = 0; i < adj[u].size(); ++i)
    {
        int v = adj[u][i];
        if (!visited[v])
        {
            DFSTransposed (v, adj, visited, component);
        }
    }
}

void find_strongly_connected_comp (int n, vector<vector<int>>& adj, vector<vector<int>>& adjTransposed)
{
    vector<bool> visited (n, false);
    stack<int> dfsTransOrder;
    vector<int> component;

    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
        {
            DFS (i, adj, visited, dfsTransOrder);
            dfsTransOrder.push (i);
        }
    }
    for (int i = 0; i < n; ++i)
    {
        visited[i] = false;
    }
    int nr=0;
    //g<<nr<<endl;
    vector<vector<int>> v;
    while (!dfsTransOrder.empty() )
    {
        int i = dfsTransOrder.top();
        dfsTransOrder.pop();
        if (!visited[i])
        {
            component.clear();
            DFSTransposed (i, adjTransposed, visited, component);
            nr++;
            v.push_back(component);
            //g << '\n';
        }
    }
    g<<nr<<endl;
    vector <int>::iterator itr;
    for(int i=0;i<nr;i++)
    {
        for (itr = v[i].begin(); itr != v[i].end(); ++itr)
            g << *itr << " ";
        g<<endl;
    }
}

int main()
{
    int n, m;
    vector<vector<int>> adj, adjTransposed;

    read (n, m, adj, adjTransposed);

    //print(n, m, adj);

    find_strongly_connected_comp (n, adj, adjTransposed);

    return 0;
}
