#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stack>
#include <set>
#include <climits>
#include <queue>

using namespace std;

ifstream f("graf.in");
int maxi = 0;
int cnr;
set<int, greater<int> > s;
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

void empty_stack(int i, int j, vector<vector<pair<int,int>>>& bicon_comp, stack<pair<int,int>>& st){
    vector<pair<int,int>> new_comp;
    pair<int,int> ij_edge(i, j), ji_edge(j, i);

    pair<int,int> edge = st.top();
    new_comp.push_back(edge);
    st.pop();
    while (edge != ij_edge && edge != ji_edge){
        edge = st.top();
        new_comp.push_back(edge);
        st.pop();
    }

    bicon_comp.push_back(new_comp);
}

void DFS(int i, const vector<vector<int>>& adj, vector<bool>& visited, vector<int>& nivel, vector<int>& niv_min, vector<vector<pair<int,int>>>& bicon_comp, stack<pair<int,int>>& st){
    visited[i] = true;
    niv_min[i] = nivel[i];

    for (int k = 0; k < adj[i].size(); ++k){
        int j = adj[i][k];
        if (!visited[j]){
            nivel[j] = nivel[i] + 1;
            st.push({i, j});

            DFS(j, adj, visited, nivel, niv_min, bicon_comp, st);
            niv_min[i] = min(niv_min[i], niv_min[j]);    // actualizare niv_min[i]
            if (niv_min[j] >= nivel[i]){                  // test punct critica
                empty_stack(i, j, bicon_comp, st);
            }
        } else if (nivel[i] - nivel[j] > 1){
            niv_min[i] = min(niv_min[i], nivel[j]);      // actualizare niv_min[i]
            st.push({i, j});
        }
    }
}

void find_bicon_comp(int n, const vector<vector<int>>& adj, vector<vector<pair<int,int>>>& bicon_comp){
    vector<bool> visited(n, false);
    vector<int> niv_min(n);
    vector<int> nivel(n);
    stack<pair<int,int>> st;

    for (int i = 0; i < n; ++i){
        if (!visited[i]){
            nivel[i] = 1;
            DFS(i, adj, visited, nivel, niv_min, bicon_comp, st);
        }
    }
}

void print_bicon_comp(vector<vector<pair<int,int>>>& bicon_comp){
    int maxi = 0;
    for (int i = 0; i < bicon_comp.size(); ++i){
        //cout << "Comp. " << i + 1 << ":" << endl;
        int nr=0;
        for (int j = 0; j < bicon_comp[i].size(); ++j){
            //cout << bicon_comp[i][j].first + 1 << ' ' << bicon_comp[i][j].second + 1 << '\n';
            nr++;
        }
        if (nr>maxi)
        {
            maxi = nr;
            cnr = i;
        }
        //cout << endl;
    }
    for (int j = 0; j < bicon_comp[cnr].size(); ++j)
    {
        s.insert(bicon_comp[cnr][j].first + 1);
        s.insert(bicon_comp[cnr][j].second + 1);
    }
    set<int, greater<int> >::iterator itr;
    for (itr = s.begin(); itr != s.end(); ++itr)
        cout << *itr << " ";
    cout<<endl;
    for (int j = 0; j < bicon_comp[cnr].size(); ++j)
        cout << bicon_comp[cnr][j].first + 1 << ' ' << bicon_comp[cnr][j].second + 1 << '\n';
}

int main()
{
    int n, m;
    vector<vector<int>> adj;
    vector<vector<pair<int,int>>> bicon_comp;

    read(n, m, adj);

    find_bicon_comp(n, adj, bicon_comp);

    print_bicon_comp(bicon_comp);

    return 0;
}
