#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    int m, n;
    while (cin>>m>>n) {
        vector<int> costo(n), favor(n);
        for (int i = 0; i < n; ++i) {
            cin >> costo[i] >> favor[i];
        }

        int m_original = m;
        if (m > 1800) m += 200;

        vector<int> PD(m + 1, -1);
        PD[0] = 0;

        for (int i = 0; i < n; ++i) {
            for (int w = m; w >= costo[i]; --w) {
                if (PD[w - costo[i]] != -1) {
                    PD[w] = max(PD[w], PD[w - costo[i]] + favor[i]);
                }
            }
        }

        int res = 0;
        for (int gastado = 0; gastado <= m; ++gastado) {
            if (PD[gastado] == -1) continue;
            if ((m_original > 2000) || (gastado <= m_original || gastado > 2000)) {
                res = max(res, PD[gastado]);
            }
        }

        cout << res << '\n';
    }
    return 0;
}