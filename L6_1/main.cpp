#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int nmax = 1005;
int v, e;
vector<int> G[nmax];

bool visited[nmax];
int d[nmax];
int colour[nmax];

const int maxcolour = 6;

int main() {
    freopen("3color.in", "r", stdin);
    freopen("3color.in", "w", stdout);

    cin >> v >> e;
    cout << v << " " << e << endl;
    for (int i = 0; i < e; i++) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
        d[x]++;
        d[y]++;
    }

    queue<int> Q;
    for (int i = 0; i < v; i++) {
        if (d[i] <= maxcolour - 1) {
            cout << "good " << i << " " << d[i] << endl;
            visited[i] = true;
            Q.push(i);
        }
    }

    while(!Q.empty()) {
        int node = Q.front();
        Q.pop();

        cout << "pop " << node << endl;

        // culorile sunt de la 1 la maxcolour
        // poz. 0 e nefolosita
        bool used_colours[maxcolour + 1] = {false};
        for (auto next: G[node]) {
            d[next]--;            // micsoram gradul
            if (!visited[next]) { // daca nu e vizitat si are gradul suf. de mic
                visited[next] = true;
                if (d[next] <= maxcolour - 1) Q.push(next);
            }
            used_colours[colour[next]] = true;
            cout << "neighbour " << next << " uses " << colour[next] << endl;
        }
        for (int i = 1; i <= maxcolour; i++) {
            if (!used_colours[i]) {
                colour[node] = i;
                break;
            }
        }
    }

    for (int i = 0; i < v; i++) {
        cout << colour[i] << " ";
    }
    cout << "\n";

    return 0;
}
