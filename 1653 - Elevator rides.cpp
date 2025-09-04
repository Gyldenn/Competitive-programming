#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, limite;
    cin >> n >> limite;

    vector<int> pesos(n);
    for (int& x : pesos) cin >> x;

    // dp[mask] = {cantidad de subconjuntos usados, peso actual en el último subconjunto}
    vector<pair<int, int>> dp(1 << n, {n + 5, 0});
    dp[0] = {0, limite + 1}; // Caso base: conjunto vacío

    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                auto [cant, peso_actual] = dp[mask ^ (1 << i)];

                if (peso_actual + pesos[i] > limite) {
                    // Nuevo subconjunto
                    cant++;
                    peso_actual = pesos[i];
                } else {
                    peso_actual += pesos[i];
                }

                dp[mask] = min(dp[mask], {cant, peso_actual});
            }
        }
    }
    cout << dp[(1 << n) - 1].first << endl;
    return 0;
}