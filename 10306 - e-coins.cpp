#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <functional>
#include <climits>
#include <cmath>
#include <queue>
#include <set>

using namespace std;

const set<int> cuadrados = {1*1,2*2,3*3,4*4,5*5,6*6,7*7,8*8,9*9,10*10,11*11,12*12,13*13,14*14,15*15,16*16,17*17,18*18,19*19,20*20,21*21,22*22,23*23,24*24};

int cambio_exacto(const vector<int>& e_values, int pago) {
    const int INF = INT_MAX-1;
    vector<int> PD(pago + 1, INF);
    PD[0] = 0;

    for (int valor : e_values) {
        for (int i = valor; i <= pago; ++i) {
            if (PD[i - valor] != INF) {
                PD[i] = min(PD[i], PD[i - valor] + 1);
            }
        }
    }

    return PD[pago] == INF ? -1 : PD[pago];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, s, conv_value, IT_value, res; cin>>n;

    while(n--){
        cin>>m>>s;
        vector<int> e_values;
        for(int i= 0 ; i<m ; i++) {
            cin>>conv_value>>IT_value;
            int value = conv_value*conv_value + IT_value*IT_value;
            if (cuadrados.find(value) != cuadrados.end()) e_values.push_back(value);
        } 

        res = cambio_exacto(e_values, s*s);
        if (res != -1)
            cout << res << endl;
        else
            cout << "not possible" << endl;

    }
    return 0;
}