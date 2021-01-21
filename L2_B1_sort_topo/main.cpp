#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

ifstream f ("sortaret.in");
ofstream g ("sortaret.out");

void read (int& n, int& m, vector<vector<int>>& adj, vector<int>& inDegree)
{
    int x, y;
    f >> n >> m;

    for (int i = 0; i < n; ++i)
    {
        vector<int> v;
        adj.push_back (v);

        inDegree.push_back (0);
    }

    for (int i = 0; i < m; ++i)
    {
        f >> x >> y;
        --x;
        --y;
        adj[x].push_back (y);

        ++inDegree[y];
    }
}

vector<int> top_sorting (int n, vector<vector<int>>& adj, vector<int>& inDegree)
{
    vector<int> result;
    priority_queue<int> q;
    for (int i = 0; i < inDegree.size(); ++i)
    {
        if (inDegree[i] == 0)
        {
            q.push (i);
        }
    }

    while (!q.empty() )
    {
        int u = q.top();
        q.pop();
        result.push_back (u);

        for (int i = 0; i < adj[u].size(); ++i)
        {
            int j = adj[u][i];
            if (--inDegree[j] == 0)
            {
                q.push (j);
            }
        }
    }
    return result;
}

int main()
{
    int n, m;
    vector<vector<int>> adj;
    vector<int> inDegree;
    vector<int> sorted;

    read (n, m, adj, inDegree);

    sorted = top_sorting (n, adj, inDegree);

    for (int i = 0; i < sorted.size(); ++i)
    {
        g << sorted[i] + 1 << ' ';
    }

    return 0;
}
