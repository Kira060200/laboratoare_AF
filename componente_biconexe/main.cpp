#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stack>
#include <climits>
#include <queue>
#include <set>
using namespace std;

ifstream f("biconex.in");
//ifstream f("grader_test9.in");
ofstream g("biconex.out");
int maxi = 0;
int nr;
int n, m;
vector<set<int, greater<int> >> v;
void read(int& n, int& m, vector<vector<int>>& adj){
    int x, y;
    f >> n >> m;

    for(int i = 0; i < n; ++i){
        vector<int> v;
        adj.push_back(v);
    }

    for (int i = 0; i < m; ++i){
        f >> x >> y;
        --x; --y;

        adj[x].push_back(y);
        adj[y].push_back(x);
    }
}

void empty_stack(int i, int j, stack<pair<int,int>>& st){
    nr++;

    set<int, greater<int> > s1;
    pair<int,int> ij_edge(i, j), ji_edge(j, i);

    pair<int,int> edge = st.top();
    s1.insert(edge.first+1);
    s1.insert(edge.second+1);
    st.pop();
    while (edge != ij_edge && edge != ji_edge){
        edge = st.top();
        s1.insert(edge.first+1);
        s1.insert(edge.second+1);
        st.pop();
    }
    v.push_back(s1);
}

void DFS(int i, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& nivel, vector<int>& niv_min, stack<pair<int,int>>& st){
    visited[i] = true;
    niv_min[i] = nivel[i];

    for (int k = 0; k < adj[i].size(); ++k){
        int j = adj[i][k];
        if (!visited[j]){
            nivel[j] = nivel[i] + 1;
            st.push({i, j});

            DFS(j, adj, visited, nivel, niv_min, st);
            niv_min[i] = min(niv_min[i], niv_min[j]);    // actualizare niv_min[i]
            if (niv_min[j] >= nivel[i]){                  // test punct critica
                empty_stack(i, j, st);
            }
        } else if (nivel[i] - nivel[j] > 1){
            niv_min[i] = min(niv_min[i], nivel[j]);      // actualizare niv_min[i]
            st.push({i, j});
        }
    }
}

void find_bicon_comp(int n, const vector<vector<int>>& adj){
    vector<bool> visited(n, false);
    vector<int> niv_min(n);
    vector<int> nivel(n);
    stack<pair<int,int>> st;

    for (int i = 0; i < n; ++i){
        if (!visited[i]){
            nivel[i] = 1;
            DFS(i, adj, visited, nivel, niv_min, st);
        }
    }
}

int main()
{
    vector<vector<int>> adj;

    read(n, m, adj);

    find_bicon_comp(n, adj);

    g<<nr<<endl;
    set<int, greater<int> >::iterator itr;
    for(int i=0;i<nr;i++)
        {
            for (itr = v[i].begin(); itr != v[i].end(); ++itr)
                g << *itr << " ";
            g<<'\n';
        }
    return 0;
}
