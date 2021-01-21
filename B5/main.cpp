#include <iostream>
#include <bits/stdc++.h>
using namespace std;

ifstream f ("graf.in");
ofstream g ("graf.out");

const int N_MAX = 100005;

int n, m, x, y;
int k;
vector <int> graph[N_MAX];
queue <int> q;
bool viz[2][N_MAX];
int dist[2][N_MAX];
int verif[N_MAX];
vector <int> solution;


void bfs (int x, int k)
{
    q.push(x);
    viz[k][x] = true;
    while(!q.empty())
    {
        int current = q.front();
        q.pop();
        for (int i : graph[current])
            if (!viz[k][i])
            {
                q.push(i);
                viz[k][i] = true;
                dist[k][i] = dist[k][current] + 1;
            }
    }
}

int main() {

    f >> n >> m >> x >> y;
    for (int i = 1; i <= m; ++i)
    {
        int a , b;
        f >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    bfs (x, 0);
    bfs(y, 1);

    for (int i = 1; i <= n; ++i)
    {
        if (dist[0][i] + dist[1][i] == dist[0][y])
        {
            verif[dist[0][i]] ++;
        }
    }

    for (int i = 1; i <= n; ++i)
    {
        if (dist[0][i] + dist[1][i] == dist[0][y] and verif[dist[0][i]] == 1)
            solution.push_back(i);
    }
    g << solution.size() << '\n';
    for (int i=0; i<solution.size(); i++)
    {
        g << solution[i] << " ";
    }
    return 0;
}
