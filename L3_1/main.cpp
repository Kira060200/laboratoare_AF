#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

ifstream f("grafpond.in");

class Edge{
    int src;
    int dst;
    int weight;
public:
    Edge(int s, int d, int w) : src(s), dst(d), weight(w) {}

    int get_src() { return src; }
    int get_dst() { return dst; }
    int get_weight() { return weight; }
};

bool compareEdge(Edge* e1, Edge* e2){
    return e1->get_weight() < e2->get_weight();
}

void print_graph(vector<Edge*>& edge_list){
    for (int i = 0; i < edge_list.size(); ++i){
        cout << edge_list[i]->get_src() + 1 << ' ' << edge_list[i]->get_dst() + 1 << ' ' << edge_list[i]->get_weight() << '\n';
    }
    cout << endl;
}

void read(int& n, int& m, int*& father, int*& height, vector<Edge*>& edge_list){
    int x, y, z;

    f >> n >> m;

    father = new int[n];
    height = new int[n];

    for(int i = 0; i < m; ++i){
        f >> x >> y >> z;
        Edge* ed = new Edge(--x, --y, z);

        edge_list.push_back(ed);
    }
}

void sort_graph(vector<Edge*>& edge_list){
    sort(edge_list.begin(), edge_list.end(), compareEdge);
}

void initialize(int n, int*& father, int*& height){
    for(int i = 0; i < n; ++i){
        father[i] = -1;
        height[i] = 0;
    }
}

int repres(int u, int* father){
    while (father[u] != -1){
        u = father[u];
    }
    return u;
}

void join(int ru, int rv, int* father, int* height){
    if (height[ru] > height[rv]){
        father[rv] = ru;
    } else {
        father[ru] = rv;
        if (height[ru] == height[rv]){
            height[rv]++;
        }
    }
}

void deallocate_mem(int* father, int* height, vector<Edge*>& edge_list, vector<Edge*>& apcm){
    delete[] father;
    delete[] height;
    for (int i = 0; i < edge_list.size(); ++i){
        delete edge_list[i];
    }
    for (int i = 0; i < apcm.size(); ++i){
        delete apcm[i];
    }
}

int main()
{
    int n, m, *father, *height, num_sel_edges = 0;
    vector<Edge*> edge_list;
    vector<Edge*> apcm;

    read(n, m, father, height, edge_list);

    sort_graph(edge_list);
    initialize(n, father, height);

    for (int i = 0; i < m; ++i){
        Edge* edge = edge_list[i];
        int ru = repres(edge->get_src(), father);
        int rv = repres(edge->get_dst(), father);

        if (ru != rv){
            Edge* apcm_edge = new Edge(edge->get_src(), edge->get_dst(), edge->get_weight());
            apcm.push_back(apcm_edge);

            join(ru, rv, father, height);

            num_sel_edges++;
            if (num_sel_edges == n - 1){
                break;
            }

        }
    }
    print_graph(apcm);

    deallocate_mem(father, height, edge_list, apcm);
    return 0;
}
