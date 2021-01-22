#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

ifstream f ("retea2.in");
ofstream g ("retea2.out");

typedef pair <long long, int> PLLI;

double sol;

struct punct {
    int x, y;
};

punct *Centrale, *Bloc;

int N, M;

bool *sel;

long long Dist (punct A, punct B) {
    return 1LL * (A.x - B.x) * (A.x - B.x) + 1LL * (A.y - B.y) * (A.y - B.y);
}

long long *Best;

int main()
{
    f >> N >> M;
    Centrale = new punct [N+1];
    Bloc = new punct [M+1];
    sel = new bool[M+1];
    for (int i = 0; i < N; ++ i ) {
        f >> Centrale[i].x >> Centrale[i].y;
    }
    for (int i = 0; i < M; ++ i ) {
        f >> Bloc[i].x >> Bloc[i].y;
    }

    Best = new long long[M+1];
    for (int i = 0; i < M; ++ i )  {
        Best[i] = -1;
    }

    for (int i = 0; i < N; ++ i ) {
        for (int j = 0; j < M; ++ j ) {
            long long val = Dist(Centrale[i], Bloc[j]);

            if (val < Best[j] || Best[j] == -1) {
                Best[j] = val;
            }
        }
    }

    for (int road = 1; road <= M; ++ road) {
        int ind = -1;
        for (int i = 0; i < M; ++ i ) {
            if (sel[i]) continue;

            if (ind == -1) {
                ind = i;
                continue;
            }

            if (Best[ind] > Best[i])
                ind = i;
        }

        sol = sol + sqrt(Best[ind]);
        sel[ind] = 1;

        for (int i = 0; i < M; ++ i ) {
            if (sel[i]) continue;

            long long val = Dist(Bloc[ind], Bloc[i]);

            Best[i] = min(Best[i], val);
        }
    }

    g << setprecision(6) << fixed << sol << '\n';

    return 0;
}
