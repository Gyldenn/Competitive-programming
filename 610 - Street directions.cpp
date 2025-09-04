
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1005;

int n, m;
vector<int> adj[MAXN];
int discovery[MAXN], low[MAXN], parent[MAXN];
bool visited[MAXN];
int timer;
vector<pair<int, int>> result;

void findBridges(int u) {
    visited[u] = true;
    discovery[u] = low[u] = ++timer;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            parent[v] = u;
            findBridges(v);
            
            low[u] = min(low[u], low[v]);
            
            if (low[v] > discovery[u]) {
                // Puente encontrado - debe mantenerse bidireccional
                result.push_back({u, v});
                result.push_back({v, u});
            } else {
                // No es puente - asignar dirección u->v
                result.push_back({u, v});
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], discovery[v]);
            // Asignar dirección u->v si no es puente
            if (discovery[v] < discovery[u]) { // Evitar duplicados
                result.push_back({u, v});
            }
        }
    }
}

int main() {
    int caseNum = 1;
    while (cin >> n >> m && (n != 0 || m != 0)) {
        // Inicialización
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            discovery[i] = low[i] = parent[i] = 0;
            visited[i] = false;
        }
        result.clear();
        timer = 0;
        
        // Leer entrada
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        // Encontrar puentes y asignar direcciones
        findBridges(1);
        
        // Eliminar duplicados (pueden ocurrir en ciclos)
        sort(result.begin(), result.end());
        result.erase(unique(result.begin(), result.end()), result.end());
        
        // Ordenar el resultado para consistencia
        sort(result.begin(), result.end());
        
        // Imprimir resultado
        cout << caseNum++ << endl << endl;
        for (auto& p : result) {
            cout << p.first << " " << p.second << endl;
        }
        cout << "#" << endl;
    }
    return 0;
}