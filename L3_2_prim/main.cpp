#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
#include <climits>
#include <queue>

using namespace std;

ifstream f("apm.in");
ofstream g("apm.out");

class Edge{
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

    for (int i = 0; i < m; ++i){
        f >> x >> y >> z;
        --x; --y;

        adj[x].push_back(Edge(y, z));
        adj[y].push_back(Edge(x, z));
    }
}

void init(const int& n, int*& father){
    father = new int[n];

    for (int i = 0; i < n; ++i){
        father[i] = -1;
    }
}

void prim(const int& n, const int& m, int*& father, int start, vector<vector<Edge>>& adj){
    priority_queue<Edge> pq;
    vector<bool> selected(n, false);
    vector<int> min_weight(n, INT_MAX);

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

int main()
{
    int n, m, *father, start = 4;
    vector<vector<Edge>> adj;

    read(n, m, adj);

    prim(n, m, father, start, adj);

    for (int i = 0; i < n; ++i)
        cout << father[i] << ' ';       // root = -1

    delete[] father;

    return 0;
}
