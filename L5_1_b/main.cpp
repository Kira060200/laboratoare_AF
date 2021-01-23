#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <climits>
using namespace std;

ifstream f("retea.in");
ofstream g("retea.out");

#define n_max 1000

int n,m,s,t;
int graf[n_max][n_max],tata[n_max];
bool ok = true;
struct grade{int in,out;}a[n_max];

void read()
{
    f>>n>>s>>t>>m;
    for (int i=0;i<m;++i)
    {
        int x,y,c,fx;
        f>>x>>y>>c>>fx;
        graf[x][y] = c-fx;
        graf[y][x] = fx;

        if (c<fx)
        {
            ok = 0;
            break;
        }
        a[x].out += fx;
        a[y].in += fx;
    }

    for (int i=1;i<=n;++i)
        if (a[i].in != a[i].out && i!=s && i!=t)
        {
            ok = 0;
            break;
        }
}
bool bfs()
{
    bool viz[n_max];
    memset(viz,0,sizeof(viz));
    queue<int> q;
    q.push(s);
    viz[s] = 1;
    tata[s] = -1;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (int i=1;i<=n;++i)
            if (viz[i] == 0 && graf[x][i] > 0)
            {
                q.push(i);
                viz[i] = 1;
                tata[i] = x;
            }
    }
    return (viz[t] == true);
}

int fordFulkerson()
{
    int mx = 0;
    int x,y;


    while (bfs())
    {
        int flow = INT_MAX;
        for (x = t; x!= s; x=tata[x])
        {
            y = tata[x];
            flow = min(flow, graf[y][x]);
        }
        for (x = t; x!= s; x=tata[x])
        {
            y = tata[x];
            graf[x][y] += flow;
            graf[y][x] -= flow;
        }
        mx += flow;
    }

    return mx;
}
int main()
{
    read();
    if (ok)
    {
        g<<"DA\n";
        g<<fordFulkerson()<<'\n';



    }
    else
        g<<"NU\n";
    return 0;
}
