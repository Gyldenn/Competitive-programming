#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

#define INF 1000000

int d[1100];
int mat[1100][1100];

struct node {
    int s, t, w;
    node(int _s=0, int _t=0, int _w=0) {
        s=_s;
        t=_t;
        w=_w;
    }
};

int main() {
    int c;
    vector<node> V;
    cin >> c;

    while (c--) {
        int i, j, k;
        memset(mat, 0, sizeof(mat));
        V.clear();

        int n, m;
        cin >> n >> m;

        int x, y, t;
        while (m--) {
            cin >> x >> y >> t;
            V.push_back(node(x, y, t));
        }

        bool possible = false;
        // for (k = 0; k < n; k++)  <--- esta línea está comentada
        k = 0; // pero k igual se usa como 0

        for (i = 0; i < n; i++)
            d[i] = INF;
        d[k] = 0;

        for (i = 0; i < n; i++) {
            for (j = 0; j < V.size(); j++) {
                if (d[V[j].s] != INF) {
                    if (d[V[j].s] + V[j].w < d[V[j].t])
                        d[V[j].t] = V[j].w + d[V[j].s];
                }
            }
        }

        for (j = 0; j < V.size(); j++) {
            if (d[V[j].t] > d[V[j].s] + V[j].w)
                possible = true;
        }

        if (possible)
            cout << "possible" << endl;
        else
            cout << "not possible" << endl;
    }

    return 0;
}
