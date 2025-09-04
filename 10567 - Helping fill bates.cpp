#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

string cadena;
vector<vector<int>> letras(128);

int main() {
    cin >> cadena;
    int n = cadena.size();
    for (int i = 0; i < n; i++) {
        letras[cadena[i]].push_back(i);
    }
    int casos;
    cin >> casos;
    while (casos--) {
        string palabra;
        cin >> palabra;
        bool matched = true;
        int first = -1, last = -1;
        int current_pos = -1;

        for (char c : palabra) {
            auto it = upper_bound(letras[c].begin(), letras[c].end(), current_pos);
            if (it == letras[c].end()) {
                matched = false;
                break;
            }
            current_pos = *it;
            if (first == -1) {
                first = current_pos;
            }
            last = current_pos;
        }

        if (matched) {
            cout << "Matched " << first << " " << last << endl;
        } else {
            cout << "Not matched" << endl;
        }
    }
    return 0;
}