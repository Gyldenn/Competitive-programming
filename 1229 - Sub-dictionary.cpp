//implementacion de sub-dictionary


#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stack>
#include <string>
#include <map>
#include <sstream>
#include <iterator>
using namespace std;
using Graph = vector<vector<int>>;

vector<string> splitLineToVector(const string& line) {
    istringstream iss(line);
    return {istream_iterator<string>{iss}, istream_iterator<string>{}};
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
    ios ::sync_with_stdio(false);
    cin.tie(0);
    int N; cin >> N;
    while(N!=0) {
        Graph grafo(N);
        Graph grafoTranspuesto(N);
        vector<vector<string>> pal(N);
        map<string, int> indices;
        
        //armo el grafo con las definiciones y sus palabras (sin repetidas)
        for(int i = 0; i < N; i++) {
            string linea;
            getline(cin, linea);
            vector<string> palabras = splitLineToVector(linea);
            string def = palabras[0];

            indices[def] = i; // Asignamos un índice a la definición

            palabras.erase(palabras.begin()); // Elimina la definición
            sort(palabras.begin(), palabras.end());
            palabras.erase(unique(palabras.begin(), palabras.end()), palabras.end());
            // Elimina palabras repetidas

            pal[i] = palabras; // Guardamos las palabras asociadas a la definición
        }
        // Ahora construyo el grafo
        for(int i=0; i<N; i++){
            for (string& palabra : pal[i]) {
                grafo[indices[palabra]].push_back(i); // Agrego la dependencia de definiciones al grafo
                grafoTranspuesto[i].push_back(indices[palabra]); // Ahora al transpuesto
            } 
        }
        //ya tengo un grafo con las definiciones y sus palabras asociadas armado
        //ahora busco scc

        // Primera pasada DFS para obtener el orden de finalización
        vector<bool> visited(N, false);
        vector<int> order;
        for (int i = 0; i < N; i++) {
            if (!visited[i]) {
                dfs(grafo, i, visited, order);
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
                dfs(grafoTranspuesto, v, visited, component_order);
                for (int w : component_order) {
                    component[w] = current_component;
                }
                current_component++;
            }
        }

        // contar el largo de las componentes scc
        vector<int> component_size(current_component, 0);
        for (int comp : component) {
            component_size[comp]++;
        }
        // encontrar la componente mas pequeña
        int min_size = N + 1; // Inicializar con un valor mayor que cualquier componente
        for (int size : component_size) {
            if (size > 0 && size < min_size) {
                min_size = size;
            }
        }
        // Imprimir el resultado
        cout << min_size << endl;
        // Leer el siguiente valor de N

        cin >> N;
    }
    return 0;
}