#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stack>
using namespace std;
using Graph = vector<vector<int>>;

vector<int> ordenTopologico(Graph& grafo) {
    int n = grafo.size();
    vector<int> orden;
    vector<int> estado(n, 0); // 0 = no visitado, 1 = en proceso, 2 = visitado
    stack<int> pila;
    bool ciclo = false;

    function<void(int)> dfs = [&](int nodo) {
        if (ciclo) return;
        estado[nodo] = 1; // Marcamos como en proceso
        
        for (int vecino : grafo[nodo]) {
            if (estado[vecino] == 0) {
                dfs(vecino);
            } else if (estado[vecino] == 1) {
                // Encontramos un ciclo
                ciclo = true;
                return;
            }
        }
        
        estado[nodo] = 2; // Marcamos como visitado
        pila.push(nodo);
    };

    for (int i = 0; i < n && !ciclo; ++i) {
        if (estado[i] == 0) {
            dfs(i);
        }
    }

    if (ciclo) {
        return {}; //vector vacío para indicar ciclo
    }

    while (!pila.empty()) {
        orden.push_back(pila.top());
        pila.pop();
    }

    return orden;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    Graph grafo(n);
    while (m--) {
        int a, b;
        cin >> a >> b;
        grafo[a-1].push_back(b-1);
    }
    
    vector<int> orden = ordenTopologico(grafo);
    
    if (orden.empty()) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        for (int i = 0; i < n; ++i) {
            cout << orden[i] + 1 << " ";
        }
        cout << endl;
    }
    
    return 0;
}