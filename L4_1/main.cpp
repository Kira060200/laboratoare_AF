#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
#include <climits>
#include <queue>

using namespace std;

ifstream f ("activitati.in");
ofstream g ("iesire.out");
int *w, *d, *tata;
int sum=0;
class Edge
{
    int node;
    int weight;
public:
    Edge (int n, int w) : node (n), weight (w) {}

    int get_node() const
    {
        return node;
    }
    int get_weight() const
    {
        return weight;
    }
};

void read (int& n, int& m, vector<vector<Edge>>& adj, vector<int>& inDegree, vector<int>& outDegree) //varfuri, muchii, lista de adiacenta, vector de grade interioare, vector grade exterioare
{
    int x, y;
    f >> n ;
    w = new int[n];
    for (int i = 0; i < n; i++)
        f >> w[i];
    f >> m;

    for (int i = 0; i < n+2; ++i)
    {
        vector<Edge> v;
        adj.push_back (v);

        inDegree.push_back (0);
        outDegree.push_back (0);
    }
    for (int i = 0; i < m; ++i)
    {
        f >> x >> y;
        --x;
        --y;

        adj[x].push_back (Edge (y, w[x]) );
        ++inDegree[y];
        ++outDegree[x];
    }
    f.close();
}

void init (const int& n, int*& tata)
{

}

vector<int> top_sorting (int n, vector<vector<Edge>>& adj, vector<int>& inDegree)
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
            int j = adj[u][i].get_node();

            if (--inDegree[j] == 0)
            {
                q.push (j);
            }
        }
    }
    return result;
}

void solve (const int& n, const int& m, int start, vector<vector<Edge>>& adj, vector<int>& inDegree)
{
    vector<int> sorted;
    d=new int[n];
    for(int i=0;i<n;++i)
        d[i]=INT_MIN;

    tata = new int[n];
    for (int i = 0; i < n; ++i)
    {
        tata[i] = -1;
    }
    d[start] = 0;

    sorted = top_sorting (n, adj, inDegree);
    /*for(int i = 0; i < sorted.size(); ++i)
        cout<<sorted[i]+1<< ' ';
    cout<<endl;*/
    for (int i = 0; i < sorted.size(); ++i)
    {
        int u = sorted[i];

        if (d[u] != INT_MIN)
        {
            for (int j = 0; j < adj[u].size(); ++j)
            {
                int v = adj[u][j].get_node();
                int weight = adj[u][j].get_weight();

                if (d[u] + weight > d[v])
                {
                    d[v] = d[u] + weight;
                    tata[v] = u;
                }
            }
        }
    }
    for(int i=0;i<n;i++)
        if(sum<d[i])
            sum=d[i];
}

void print_sol (int n, int s, int v, int* tata)
{
    if (tata[v] != s)
    {
            v = tata[v];
            print_sol(n, s, v, tata);
            g << v + 1 << ' ';
    }
}

int main()    // FOR DIRECTED ACYCLIC GRAPHS (+NEGATIVE WEIGHTS)
{
    int n, m, s, t;
    vector<vector<Edge>> adj;
    vector<int> inDegree;
    vector<int> outDegree;

    read (n, m, adj, inDegree, outDegree);

    s = ++n;
    t = ++n;
    inDegree[s-1]=0;
    for(int i=0;i<n-2;i++)
        if(!inDegree[i])
                adj[s-1].push_back (Edge (i, 0) );
        else if(!outDegree[i])
            {
                adj[i].push_back (Edge (t-1, w[i]) );
                inDegree[t-1]++;
            }
    /*for(int i=0;i<n;i++)
        {
            cout<<i+1<<": ";
            for(int j=0;j<adj[i].size();j++)
                cout<<adj[i][j].get_node()+1<<" "<<adj[i][j].get_weight()<<", ";
            cout<<endl;
        }*/
    solve (n, m, s-1, adj, inDegree);
    g<<"Timp minim "<<sum<<endl<<"Activitati critice: ";
    print_sol (n, s-1, t-1, tata);
    g<<endl;
    for(int i=0;i<n-2;i++)
        g<<i+1<<": "<<d[i]<<' '<<d[i]+w[i]<<endl;

    delete[] tata;
    delete[] d;
    delete[] w;
    g.close();
    return 0;
}
