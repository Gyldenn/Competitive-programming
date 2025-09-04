#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int bottomUp(const vector<vector<int>>& bellotas, int arboles, int h, int caida) {
    vector<int> v1(arboles, 0), v2(arboles, 0);
    vector<int> mejor_en_nivel(h, 0);  // guarda el mejor valor global en cada nivel

    for (int nivel = 0; nivel < h; nivel++) {
        int mejor_salto = (nivel >= caida) ? mejor_en_nivel[nivel - caida] : 0;

        int mejor_en_este_nivel = 0;
        for (int arb = 0; arb < arboles; arb++) {
            int mantener = (nivel > 0) ? v1[arb] : 0;
            v2[arb] = bellotas[arb][nivel] + max(mantener, mejor_salto);
            mejor_en_este_nivel = max(mejor_en_este_nivel, v2[arb]);
        }

        mejor_en_nivel[nivel] = mejor_en_este_nivel;
        swap(v1, v2);
    }

    return *max_element(v1.begin(), v1.end());
}

int main() {
    int test_cases;
    cin >> test_cases;

    while (test_cases--) {
        int arboles, h, caida;
        cin >> arboles >> h >> caida;

        vector<vector<int>> bellotas(arboles, vector<int>(h, 0));
        for (int t = 0; t < arboles; t++) {
            int k;
            cin >> k;
            while (k--) {
                int nivel;
                cin >> nivel;
                bellotas[t][nivel - 1]++;
            }
        }

        cout << bottomUp(bellotas, arboles, h, caida) << endl;
    }

    return 0;
}