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
struct date
{
    int x;
    int y;
    int z;
};
vector <date> muchie;
int *d, *tata;
int n, m;
int start;
int t;
int negative_cycle = -1;

void read ()
{
    int x, y, z;
    f >> n >> m;

    tata = new int[n];
    d = new int[t];

    for (int i = 0; i < n; ++i)
    {
        date v;
        muchie.push_back (v);
        tata[i]=-1;
        d[i]=INT_MAX;
    }

    for (int i = 0; i < m; ++i)
    {
        f >> x >> y >> z;
        --x;
        --y;

        muchie[i].x=x;
        muchie[i].y=y;
        muchie[i].z=z;
    }
}

void bellman_ford ()
{
    d[start] = 0;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int u = muchie[j].x;
            if (d[u] != INT_MAX)
            {
                int v = muchie[j].y;
                int w = muchie[j].z;
                if (d[u] + w < d[v])
                {
                    d[v] = d[u] + w;
                    tata[v] = u;
                }
            }
        }
    }
    int changed_node = -1;
    for (int j = 0; j < m; ++j)
    {
        int u = muchie[j].x;
        if (d[u] != INT_MAX)
        {
            int v = muchie[j].y;
            int w = muchie[j].z;
            if (d[u] + w < d[v])
            {
                d[v] = d[u] + w;
                tata[v] = u;
                changed_node = v;

            }
        }
    }
    if (changed_node != -1)
        negative_cycle = changed_node;
}

void print_solution ()
{
    /*for (int i = 0; i < n; ++i)
    {
        cout << tata[i] + 1 << ' ';
    }*/

    if (negative_cycle != -1)
    {
        cout << "\nGraful contine circuit de cost negativ:\n";
        for (int i = 0; i < n; ++i)
        {
            negative_cycle = tata[negative_cycle];
        }
        int temp = negative_cycle;
        while (tata[temp] != negative_cycle)
        {
            cout << temp + 1 << ' ';
            temp = tata[temp];
        }
        cout << temp + 1 << ' ' << tata[temp] + 1 << '\n';
    }
    else
    {
        cout<<"\nDistanta: "<<d[t];
        cout << '\n';
        if (tata[t] != -1)
        {
            while (tata[t] != -1)
            {
                cout << t + 1 << ' ';
                t = tata[t];
            }
            cout << t + 1 << ' ';
        }
        else
        {
            cout << "Unreachable node.";
        }
    }
}

int main()
{
    read();
    cout << "Vf start: ";
    cin >> start;
    --start;
    bellman_ford ();
    for(int tt=0;tt<n;tt++)
        {
            t=tt;
            if(t!=start && negative_cycle==-1)
            {
                print_solution ();
                cout<<endl;
            }
            else
                if(negative_cycle==-1)
                    cout<<"Start=Destinatie\n";
                else
                {
                    print_solution ();
                    break;
                }
        }

    return 0;
}
