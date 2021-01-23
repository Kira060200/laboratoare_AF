#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
#include <climits>
#include <queue>

using namespace std;

ifstream f ("retea.in");
ofstream g ("retea.out");

int n,m,s,t;
long **capacity, **flow;
vector<vector<int>> adj_in, adj_out;
int* tata;
bool *viz;
int max_flow = 0;
void read ()
{
    int x, y;
    long z;
    long fl;
    f >> n;
    f >> s >> t;
    f >> m;

    tata = new int[n+1];
    viz = new bool[n+1];

    capacity = new long*[n + 1];
    flow = new long*[n + 1];

    for (int i = 0; i <= n; ++i)
    {
        capacity[i] = new long[n + 1];
        flow[i] = new long[n + 1];

        vector<int> v;
        adj_in.push_back (v);
        adj_out.push_back (v);
    }

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
        {
            flow[i][j] = 0;
            capacity[i][j] = 0;
        }

    for (int i = 0; i < m; ++i)
    {
        f >> x >> y >> z >>fl;

        adj_out[x].push_back (y);
        adj_in[y].push_back (x);
        capacity[x][y] = z;
    }
    f.close();
}

bool find_s_t_unsaturated_path_BF ()
{
    queue<int> coada;
    for (int i = 1; i <= n; ++i)
    {
        tata[i] = 0;
        viz[i] = false;
    }
    viz[s] = true;
    coada.push (s);

    while (!coada.empty() )
    {
        int i = coada.front();

        coada.pop();
        for (int k = 0; k < adj_out[i].size(); ++k)
        {
            int j = adj_out[i][k];

            if (!viz[j] && capacity[i][j] - flow[i][j] > 0)
            {
                coada.push (j);
                viz[j] = true;
                tata[j] = i;

                if (j == t)
                    return true;
            }
        }
        for (int k = 0; k < adj_in[i].size(); ++k)
        {
            int j = adj_in[i][k];
            if (!viz[j] && flow[j][i] > 0)
            {
                coada.push (j);
                viz[j] = true;
                tata[j] = -i;

                if (j == t)
                    return true;
            }
        }
    }
    return false;
}

void revise_path_flow ()
{
    int min_residual_cap = INT_MAX;
    int p = t;
    while (p != s)
    {
        if (tata[p] > 0)
        {
            if (min_residual_cap > capacity[tata[p]][p] - flow[tata[p]][p])
            {
                min_residual_cap = capacity[tata[p]][p] - flow[tata[p]][p];
            }
            p = tata[p];
        }
        else
        {
            if (min_residual_cap > flow[p][-tata[p]])
            {
                min_residual_cap = flow[p][-tata[p]];
            }
            p = -tata[p];
        }
    }
    p = t;
    while (p != s)
    {
        if (tata[p] > 0)
        {
            flow[tata[p]][p] += min_residual_cap;
            p = tata[p];
        }
        else
        {
            flow[p][-tata[p]] -= min_residual_cap;
            p = -tata[p];
        }
    }
    max_flow += min_residual_cap;
}

void solve ()
{


    while (find_s_t_unsaturated_path_BF () )
    {
        revise_path_flow ();
    }

    g << "Max Flow: " << max_flow << endl;
    g << "Min Cut: " << endl << "{ ";
    for (int i = 1; i <= n; ++i)
    {
        if (viz[i]) g << i << ' ';
    }
    g << "}" << '\n' << "{ ";
    for (int i = 1; i <= n; ++i)
    {
        if (!viz[i]) g << i << ' ';
    }
    g << "}" << '\n';
    g.close();
    delete[] tata;
    delete[] viz;
}

int main()
{

    read ();

    solve ();

    for (int i = 0; i <= n; ++i)
    {
        delete[] capacity[i];
        delete[] flow[i];
    }
    delete[] capacity;
    delete[] flow;

    return 0;
}
