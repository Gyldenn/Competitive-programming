#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

using Graph = vector<vector<int>>;
int T, N, x, y, d;

bool conectados(const vector<int>& mina1, const vector<int>& mina2) {
    int radio = mina1[2] / 2;
    int derecha = mina1[0] - radio;
    int izq = mina1[0] + radio;
    int abajo = mina1[1] - radio;
    int arriba = mina1[1] + radio;

    return (mina2[0] >= derecha) && (mina2[0] <= izq) &&
           (mina2[1] >= abajo) && (mina2[1] <= arriba);
}

void dfs(const Graph& G, int v, vector<bool>& visited, vector<int>& order) {
    visited[v] = true;
    for (int w : G[v]) {
        if (!visited[w]) {
            dfs(G, w, visited, order);
        }
    }
    order.push_back(v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> T;
    while (T--) {
        cin >> N;

        Graph G(N), GT(N);  // Grafo original y grafo transpuesto
        vector<vector<int>> minas(N, vector<int>(3));
        
        for (int i = 0; i < N; i++) {
            cin >> x >> y >> d;
            minas[i] = {x, y, d};
        }

        // Construcción del grafo
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i != j && conectados(minas[i], minas[j])) {
                    G[i].push_back(j);
                    GT[j].push_back(i);
                }
            }
        }

        // Primera pasada DFS para obtener el orden de finalización
        vector<bool> visited(N, false);
        vector<int> order;
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                dfs(G, i, visited, order);
            }
        }

        // Segunda pasada DFS en el grafo transpuesto
        fill(visited.begin(), visited.end(), false);
        reverse(order.begin(), order.end());
        vector<int> component(N, -1);
        int current_component = 0;

        for (int v : order) {
            if (!visited[v]) {
                vector<int> component_order;
                dfs(GT, v, visited, component_order);
                for (int w : component_order) {
                    component[w] = current_component;
                }
                current_component++;
            }
        }

        // Contar SCC sin aristas de entrada
        vector<bool> tiene_entrada(current_component, false);
        for (int v = 0; v < N; v++) {
            for (int w : G[v]) {
                if (component[v] != component[w]) {
                    tiene_entrada[component[w]] = true;
                }
            }
        }

        int result = 0;
        for (int i = 0; i < current_component; i++) {
            if (!tiene_entrada[i]) {
                result++;
            }
        }

        cout << result << "\n";
    }
    return 0;
}