
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <limits>
#include <cfloat>
#include <cmath>
#include <iomanip>

using namespace std;

ifstream f("retea2.in");
ofstream g("retea2.out");

struct dd{ double x, y; };
struct di{ double x; int y;};

int n, m;

class cmp {
public:
    int operator() (di x, di y) {
        if(x.x == y.x) {
            return x.y > y.y;
        }
        return x.x > y.x;
    }
};


double ans;
double dist(dd a, dd b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main()
{
    int i;
    f >> n >> m;

    vector <dd> a(n + m + 1);
    priority_queue <di, vector<di>, cmp > heap;
    vector <double> minEdge(n + m + 1, DBL_MAX);

    for(i = 1; i <= n; i ++) {
        f >> a[i].x >> a[i].y;
        heap.push({0, i});
        minEdge[i] = 0;
    }

    for(i = n + 1; i <= n + m; i ++) {
        f >> a[i].x >> a[i].y;
    }
    vector <bool> used(n + m + 1, false);

    while(!heap.empty()) {
        di head = heap.top();
        heap.pop();

        int node = head.y;
        double cost = head.x;

        if(used[node]) continue;

        ans += cost;
        used[node] = true;

        for(int adj = n + 1; adj <= n + m; adj ++) {
            if(adj != node) {
                double dst = dist(a[node], a[adj]);
                if(dst < minEdge[adj]) {
                    minEdge[adj] = dst;
                    heap.push({dst, adj});
                }
            }
        }
    }
    g << fixed << setprecision(6) << ans << '\n';

    f.close(); g.close();
    return 0;
}
