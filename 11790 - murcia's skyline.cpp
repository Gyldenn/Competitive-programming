#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int n, c, h, w;

int subqseq(const vector<int>& altura, const vector<int>& grosor) {
    int n = altura.size();
    vector<int> PD(n, 0);

    for (int i = 0; i < n; ++i) {
        PD[i] = grosor[i];
        for (int j = 0; j < i; ++j) {
            if (altura[i] > altura[j]) {
                PD[i] = max(PD[i], PD[j] + grosor[i]);
            }
        }
    }
    return *max_element(PD.begin(), PD.end());
}

int main() {
    cin >> n;
    vector<string> res;
    int caso = 1;

    while (n--) {
        cin >> c;
        vector<int> altura(c), grosor(c);

        for (int i = 0; i < c; i++) cin >> h, altura[i] = h;
        for (int i = 0; i < c; i++) cin >> h, grosor[i] = h;

        int creciente = subqseq(altura, grosor);

        reverse(altura.begin(), altura.end());
        reverse(grosor.begin(), grosor.end());

        int decreciente = subqseq(altura, grosor);

        string res_case = "Case " + to_string(caso++) + ". ";
        if (creciente >= decreciente) {
            res_case += "Increasing (" + to_string(creciente) + "). Decreasing (" + to_string(decreciente) + ").";
        } else {
            res_case += "Decreasing (" + to_string(decreciente) + "). Increasing (" + to_string(creciente) + ").";
        }
        res.push_back(res_case);
    }

    for (const string& caso : res) {
        cout << caso << endl;
    }

    return 0;
}