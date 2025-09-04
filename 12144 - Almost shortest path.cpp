#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

using pii = pair<int, int>;
const int INF = 1e8;

vector<int> dijkstra(const vector<vector<pii>>& adj, int start) {
    int n = adj.size();
    vector<int> dist(n, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

void aristas_camino_minimo(const vector<vector<pii>>& adj, 
                          const vector<int>& dist, 
                          int u, int dest, 
                          vector<set<int>>& forbidden) {
    if (u == dest) return;
    
    for (auto [v, w] : adj[u]) {
        if (dist[u] + w == dist[v]) {
            forbidden[u].insert(v);
            aristas_camino_minimo(adj, dist, v, dest, forbidden);
        }
    }
}

int almostShortestPath(const vector<vector<pii>>& adj, int S, int D) {
    // Paso 1: Encontrar la distancia más corta desde S a todos los nodos
    vector<int> distFromS = dijkstra(adj, S);
    if (distFromS[D] == INF) return -1; // no existe camino
    
    // Paso 2: Encontrar la distancia más corta desde todos los nodos hasta D (grafo invertido)
    vector<vector<pii>> reverseAdj(adj.size());
    for (int u = 0; u < adj.size(); u++) {
        for (auto [v, w] : adj[u]) {
            reverseAdj[v].push_back({u, w});
        }
    }
    vector<int> distToD = dijkstra(reverseAdj, D);
    
    // Paso 3: Identificar las aristas que pertenecen a algún camino más corto
    vector<set<int>> forbiddenEdges(adj.size());
    for (int u = 0; u < adj.size(); u++) {
        for (auto [v, w] : adj[u]) {
            if (distFromS[u] + w + distToD[v] == distFromS[D]) {
                forbiddenEdges[u].insert(v);
            }
        }
    }
    
    // Paso 4: Construir nuevo grafo sin las aristas prohibidas
    vector<vector<pii>> newAdj(adj.size());
    for (int u = 0; u < adj.size(); u++) {
        for (auto [v, w] : adj[u]) {
            if (forbiddenEdges[u].count(v) == 0) {
                newAdj[u].push_back({v, w});
            }
        }
    }
    
    // Paso 5: Encontrar el camino más corto en el nuevo grafo
    vector<int> newDist = dijkstra(newAdj, S);
    return (newDist[D] == INF) ? -1 : newDist[D];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, S, D;
    while (cin >> N >> M, N || M) {
        cin >> S >> D;
        vector<vector<pii>> graph(N);
        for (int i = 0; i < M; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            graph[u].push_back({v, w});
        }
        
        cout << almostShortestPath(graph, S, D) << '\n';
    }
    
    return 0;
}