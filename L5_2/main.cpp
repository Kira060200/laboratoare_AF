#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
#include <climits>
#include <queue>
#include <stack>


using namespace std;

ifstream f ("graf.in");
ofstream g ("graf.out");

int n,m,s,t;
long **capacity, **flow;
vector<vector<int>> adj_in, adj_out, adj;
int* tata;
bool *viz;
int max_flow;

void read ()
{
    int x, y;
    f >> n >> m;
    tata = new int[n];
    viz = new bool[n];
    for (int i = 0; i <= n; ++i)
    {
        vector<int> v;
        adj.push_back (v);
    }

    for (int i = 0; i < m; ++i)
    {
        f >> x >> y;

        adj[x].push_back (y);
        adj[y].push_back (x);
    }
    f.close();
}

bool find_s_t_unsaturated_path_BF ()
{
    queue<int> coada;
    for (int i = 1; i <= n; ++i)
    {
        tata[i] = 0;
        viz[i] = 0;
    }
    viz[s] = 1;
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
                viz[j] = 1;
                tata[j] = i;

                if (j == t)
                    return 1;
            }
        }
        for (int k = 0; k < adj_in[i].size(); ++k)
        {
            int j = adj_in[i][k];
            if (!viz[j] && flow[j][i] > 0)
            {
                coada.push (j);
                viz[j] = 1;
                tata[j] = -i;

                if (j == t)
                    return 1;
            }
        }
    }
    return 0;
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

void build_flow (int* color)
{
    s = n + 1;
    t = n + 2;
    n += 2;

    capacity = new long*[n + 1];
    flow = new long*[n + 1];
    for (int i = 0; i <= n; ++i)
    {
        capacity[i] = new long[n + 1];
        flow[i] = new long[n + 1];
    }
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            flow[i][j] = capacity[i][j] = 0;

    for (int i = 0; i <= n; ++i)
    {
        vector<int> v;
        adj_out.push_back (v);
        adj_in.push_back (v);
    }

    int X_part = 0;
    for (int i = 1; i <= n; ++i)
    {
        int u = i;
        if (u != s && u != t)
        {
            if (color[u] == X_part)
            {
                for (int j = 0; j < adj[i].size(); ++j)
                {
                    int v = adj[i][j];
                    adj_out[u].push_back (v);
                    adj_in[v].push_back (u);
                    capacity[u][v] = 1;
                }
                adj_out[s].push_back (u);
                capacity[s][u] = 1;
            }
            else
            {
                adj_out[u].push_back (t);
                capacity[u][t] = 1;
            }
        }
    }
}

void solve (int* color)
{
    build_flow (color);

    tata = new int[n + 1];
    viz = new bool[n + 1];

    while (find_s_t_unsaturated_path_BF () )
    {
        revise_path_flow ();
    }

    g << "Max Flow: " << max_flow << endl;
    g << "Min Cut: " << endl << "{ ";

    for (int i = 1; i <= n; ++i)
        if (viz[i])
            g << i << ' ';
    g << "}" << '\n' << "{ ";

    for (int i = 1; i <= n; ++i)
    {
        if (!viz[i])
            g << i << ' ';
    }

    g << "}" << '\n';
    g << "Maximum Bipartite Matching (Cuplaj maxim):\n";

    for (int i = 1; i <= n; ++i)
        if (i != s)
            for (int j = 1; j <= n; ++j)
                if (j != t && flow[i][j] == 1)
                    g << i << ' ' << j << '\n';
    g << '\n';
    g.close();

    for (int i = 0; i <= n; ++i)
    {
        delete[] capacity[i];
        delete[] flow[i];
    }
    delete[] capacity;
    delete[] flow;
    delete[] tata;
    delete[] viz;
}

bool check_bipartite ( int*& color, int*& parent, pair<int, int>& odd_cycle)
{
    queue<int> coada;

    color = new int[n + 1];
    parent = new int[n + 1];
    for (int i = 0; i <= n; ++i)
    {
        color[i] = -1;
        parent[i] = 0;
    }

    coada.push (s);
    viz[s] = 1;
    color[s] = 0;

    while (!coada.empty() )
    {
        int u = coada.front();
        coada.pop();
        for (int i = 0; i < adj[u].size(); ++i)
        {
            int v = adj[u][i];
            if (!viz[v])
            {
                color[v] = !color[u];
                viz[v] = 1;
                parent[v] = u;
                coada.push (v);
            }
            else if (color[v] == color[u])
            {
                odd_cycle.first = u;
                odd_cycle.second = v;
                return 0;
            }
        }
    }
    return 1;
}

void print_odd_cycle (int* parent, pair<int, int>& odd_cycle)
{
    int s = odd_cycle.first;
    int t = odd_cycle.second;
    stack<int> s_st, t_st;
    vector<int> temp_vec;

    while (parent[s] != 0)
    {
        s_st.push (s);
        s = parent[s];
    }
    s_st.push (s);
    while (parent[t] != 0)
    {
        t_st.push (t);
        t = parent[t];
    }
    t_st.push (t);

    int cycle_root = -1;
    while (s_st.top() == t_st.top() )
    {
        cycle_root = s_st.top();
        s_st.pop();
        t_st.pop();
    }

    g << "Graful nu este bipartit, un ciclu impar este:\n";
    g << cycle_root << ' ';
    while (!s_st.empty() )
    {
        g << s_st.top() << ' ';
        s_st.pop();
    }
    while (!t_st.empty() )
    {
        temp_vec.push_back (t_st.top() );
        t_st.pop();
    }

    for (int i = temp_vec.size() - 1; i >= 0; --i)
    {
        g << temp_vec[i] << ' ';
    }
    g << '\n';
}

int main()
{
    int* parent, *color;
    pair<int, int> odd_cycle;

    read ();
    s=1;
    if (check_bipartite (color, parent, odd_cycle) )
        solve (color);
    else
        print_odd_cycle (parent, odd_cycle);

    delete[] parent;
    delete[] color;

    return 0;
}
