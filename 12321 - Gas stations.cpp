#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int L, G;

// Verifica si toda la carretera [0, L] está cubierta por las estaciones
bool ruta_cubierta(const vector<pair<int, int>>& intervalos) {
    int final = 0;
    for (const auto& intervalo : intervalos) {
        if (intervalo.first > final) {
            return false; // Hay un hueco no cubierto
        }
        final = max(final, intervalo.second);
        if (final >= L) break; // Ya cubrió toda la carretera
    }
    return final >= L;
}

// Calcula el máximo número de estaciones que pueden cerrarse
int innecesarias(vector<pair<int, int>>& intervalos) {
    sort(intervalos.begin(), intervalos.end());
    if (!ruta_cubierta(intervalos)) return -1;

    int count = 0;
    int final = 0;
    int i = 0;
    int n = intervalos.size();

    while (final < L) {
        int max_end = final;
        // Busca la estación que cubra más allá de current_end
        while (i < n && intervalos[i].first <= final) {
            max_end = max(max_end, intervalos[i].second);
            i++;
        }
        if (max_end == final) break; // No hay progreso
        final = max_end;
        count++; // Estación necesaria
    }

    return G - count; // Estaciones que pueden cerrarse
}

int main() {
    while (cin >> L >> G, L != 0 || G != 0) {
        vector<pair<int, int>> intervalos;
        for (int i = 0; i < G; i++) {
            int x, r;
            cin >> x >> r;
            intervalos.emplace_back(max(x - r, 0), min(x + r, L));
        }

        int res = innecesarias(intervalos);
        cout << res << endl;
    }
    return 0;
}