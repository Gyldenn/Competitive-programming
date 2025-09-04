#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 55;
double dist[MAXN][MAXN]; // matriz de distancias mínimas

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        N++; // incluir la casa (nodo 0)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                dist[i][j] = (i == j ? 0 : INF);

        for (int i = 0; i < M; ++i) {
            int u, v;
            double c;
            cin >> u >> v >> c;
            dist[u][v] = min(dist[u][v], c);
            dist[v][u] = min(dist[v][u], c);
        }

        // Floyd-Warshall
        for (int k = 0; k < N; ++k)
            for (int i = 0; i < N; ++i)
                for (int j = 0; j < N; ++j)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

        int P;
        cin >> P;
        vector<int> store(P);
        vector<double> save(P);
        for (int i = 0; i < P; ++i) {
            cin >> store[i] >> save[i];
        }

        int size = 1 << P;
        vector<vector<double>> dp(size, vector<double>(P, INF));

        // DP inicial: ir directo de casa a una tienda
        for (int i = 0; i < P; ++i)
            dp[1 << i][i] = dist[0][store[i]];

        for (int mask = 0; mask < size; ++mask) {
            for (int u = 0; u < P; ++u) {
                if (!(mask & (1 << u))) continue;
                for (int v = 0; v < P; ++v) {
                    if (mask & (1 << v)) continue;
                    int next = mask | (1 << v);
                    dp[next][v] = min(dp[next][v], dp[mask][u] + dist[store[u]][store[v]]);
                }
            }
        }

        double best = 0;
        for (int mask = 1; mask < size; ++mask) {
            double total_save = 0;
            for (int i = 0; i < P; ++i)
                if (mask & (1 << i))
                    total_save += save[i];

            for (int i = 0; i < P; ++i) {
                if (!(mask & (1 << i))) continue;
                double total_cost = dp[mask][i] + dist[store[i]][0];
                best = max(best, total_save - total_cost);
            }
        }

        if (best > 1e-6)
            printf("Daniel can save $%.2f\n", best);
        else
            printf("Don't leave the house\n");
    }
    return 0;
}
