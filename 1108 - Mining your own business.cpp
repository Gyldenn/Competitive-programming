#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <stack>
#include <set>
#include <map>
using namespace std;

const int MAXN = 50005;
vector<int> adj[MAXN];
int discovery[MAXN], low[MAXN], parent[MAXN];
bool is_articulation[MAXN];
int timer;
vector<int> articulation_points;

// Estructuras para componentes biconexas
stack<pair<int, int>> component_stack;
set<int> current_component;
map<int, int> component_articulations;
vector<set<int>> biconnected_components;

void dfs(int u) {
    discovery[u] = low[u] = ++timer;
    int children = 0;
    
    for (int v : adj[u]) {
        if (!discovery[v]) {
            children++;
            parent[v] = u;
            component_stack.push({u, v});
            dfs(v);
            low[u] = min(low[u], low[v]);
            
            // Encontrar punto de articulación
            if ((parent[u] == -1 && children > 1) || 
                (parent[u] != -1 && low[v] >= discovery[u])) {
                is_articulation[u] = true;
                
                // Extraer componente biconexa
                set<int> component;
                while (!component_stack.empty()) {
                    auto edge = component_stack.top();
                    component_stack.pop();
                    component.insert(edge.first);
                    component.insert(edge.second);
                    if (edge.first == u && edge.second == v) break;
                }
                biconnected_components.push_back(component);
            }
        } else if (v != parent[u] && discovery[v] < discovery[u]) {
            low[u] = min(low[u], discovery[v]);
            component_stack.push({u, v});
        }
    }
}

void find_biconnected_components(int n) {
    memset(discovery, 0, sizeof(discovery));
    memset(low, 0, sizeof(low));
    memset(parent, -1, sizeof(parent));
    memset(is_articulation, false, sizeof(is_articulation));
    articulation_points.clear();
    biconnected_components.clear();
    timer = 0;
    
    for (int i = 1; i <= n; ++i) {
        if (!discovery[i] && !adj[i].empty()) {
            dfs(i);
            
            // Procesar último componente
            if (!component_stack.empty()) {
                set<int> component;
                while (!component_stack.empty()) {
                    auto edge = component_stack.top();
                    component_stack.pop();
                    component.insert(edge.first);
                    component.insert(edge.second);
                }
                biconnected_components.push_back(component);
            }
        }
    }
    
    // Identificar puntos de articulación
    for (int i = 1; i <= n; ++i) {
        if (is_articulation[i]) {
            articulation_points.push_back(i);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, case_num = 1;
    while (cin >> N, N != 0) {
        // Reinicializar estructuras
        for (int i = 0; i < MAXN; ++i) {
            adj[i].clear();
        }
        
        // Leer túneles
        set<int> junctions;
        for (int i = 0; i < N; ++i) {
            int s, t;
            cin >> s >> t;
            adj[s].push_back(t);
            adj[t].push_back(s);
            junctions.insert(s);
            junctions.insert(t);
        }
        
        find_biconnected_components(MAXN - 1);
        
        // Calcular solución
        int min_shafts = 0;
        long long ways = 1;
        
        if (articulation_points.empty()) {
            // Grafo es biconexo - necesitamos 2 pozos en cualquier lugar
            min_shafts = 2;
            ways = junctions.size() * (junctions.size() - 1LL) / 2LL;
        } else {
            // Para cada componente biconexa que contiene exactamente un punto de articulación
            map<int, int> art_components;
            for (auto& component : biconnected_components) {
                int art_count = 0;
                for (int node : component) {
                    if (is_articulation[node]) art_count++;
                }
                
                if (art_count == 1) {
                    int non_art_nodes = 0;
                    for (int node : component) {
                        if (!is_articulation[node]) non_art_nodes++;
                    }
                    if (non_art_nodes > 0) {
                        min_shafts++;
                        ways *= non_art_nodes;
                    }
                }
            }
            
            // Si no hay tales componentes, necesitamos 2 pozos
            if (min_shafts == 0) {
                min_shafts = 2;
                ways = junctions.size() * (junctions.size() - 1LL) / 2LL;
            }
        }
        
        cout << "Case " << case_num++ << ": " << min_shafts << " " << ways << "\n";
    }
    
    return 0;
}