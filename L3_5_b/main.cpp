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

ifstream f("grafpond.in");

class Edge
{
    int node;
    int weight;
public:
    Edge(int n, int w) : node(n), weight(w) {}

    int get_node() const { return node; }
    int get_weight() const { return weight; }

    bool operator < (const Edge& e) const {
        return weight > e.weight;            // inverted symbols for building a min heap
    }
/*
    bool operator == (const Edge& e) const {
        return node == e.node;
    }

    bool operator != (const Edge& e) const {
        return node != e.node;
    }
*/
    friend ostream& operator << (ostream& out, const Edge& e);
};
ostream& operator << (ostream& out, const Edge& e){
    out << e.node << '/' << e.weight;
    return out;
}

void read(int& n, int& m, vector<vector<Edge>>& adj){
    int x, y, z;
    f >> n >> m;

    for(int i = 0; i < n; ++i){
        vector<Edge> v;
        adj.push_back(v);
    }

    for (int i = 0; i < m; ++i)
    {
        f >> x >> y >> z;
        --x; --y;

        adj[x].push_back(Edge(y, z));
        adj[y].push_back(Edge(x, z));
    }
    //cout<<"SUCCESS"<<endl;
}

void init(const int& n, int*& father){
    father = new int[n];

    for (int i = 0; i < n; ++i){
        father[i] = -1;
    }
}

void prim(const int& n, const int& m, int*& father, vector<int>& min_weight, int start, vector<vector<Edge>>& adj){
    priority_queue<Edge> pq;
    vector<bool> selected(n, false);

    init(n, father);

    min_weight[start] = 0;
    pq.push(Edge(start, min_weight[start]));

    while (!pq.empty()){
        int u = pq.top().get_node();
        pq.pop();
        selected[u] = true;

        for (int i = 0; i < adj[u].size(); ++i){
            int v = adj[u][i].get_node();
            int weight = adj[u][i].get_weight();

            if (!selected[v] && min_weight[v] > weight){
                min_weight[v] = weight;
                father[v] = u;

                pq.push(Edge(v, min_weight[v]));
            }
        }
    }
}

void max_weight_for_new_edge_closing_a_cycle(int* father, vector<int>& min_weight, int cost){
    int s, t, w, max_node = -1, s2, t2, w_init;
    stack<int> s_st, t_st;
    cout << "\nfirst_node: ";
    cin >> s;
    cout << "second_node: ";
    cin >> t;
    cout << "weight: ";
    cin >> w;
    s2 = s; t2 = t, w_init = w;
    --s; --t;
    while (father[s] != -1){
        s_st.push(s);
        s = father[s];
    }

    while (father[t] != -1){
        t_st.push(t);
        t = father[t];
    }
    while (!s_st.empty() && !t_st.empty() && s_st.top() == t_st.top()){
        s_st.pop();
        t_st.pop();
    }
    while (!s_st.empty()){
        int u = s_st.top();
        if (min_weight[u] > w){
            w = min_weight[u];
            max_node = u;
        }
        s_st.pop();
    }
    while (!t_st.empty()){
        int u = t_st.top();
        if (min_weight[u] > w){
            w = min_weight[u];
            max_node = u;
        }
        t_st.pop();
    }
    if (max_node == -1){
        cout << "Muchia de cost maxim din ciclul inchis de " << s2 << ' ' << t2 << " in apcm este chiar " << s2 << ' ' << t2 << " de cost " << w << '\n';
        cout << "Dupa adaugarea muchiei apcm ramane neschimbat\n";
    } else {
        cout << "Muchia de cost maxim din ciclul inchis de " << s2 << ' ' << t2 << " in apcm este " << father[max_node] + 1 << ' ' << max_node + 1 << " de cost " << w << '\n';
        cout << "Dupa adaugarea muchiei apcm are costul " << cost - w + w_init << '\n';
    }
}

int main()
{
    int n, m, *father, start = 4;
    vector<vector<Edge>> adj;
    int cost = 0;

    read(n, m, adj);
    vector<int> min_weight(n, INT_MAX);

    prim(n, m, father, min_weight, start, adj);

    cout << "Vectorul de tati al apcm este:\n";
    for (int i = 0; i < n; ++i)
        cout << father[i] << ' ';       // root = -1

    for (int i = 0; i < n; ++i){
        cost += min_weight[i];
    }
    cout << "\nCost " << cost;

    max_weight_for_new_edge_closing_a_cycle(father, min_weight, cost);

    delete[] father;

    return 0;
}
