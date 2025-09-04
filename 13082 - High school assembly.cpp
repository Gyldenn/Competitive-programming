#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int casos, n;

bool desordenado(vector<int> &v, int i) {
    int n = v.size();
    for(int j = i+1 ; j < n; ++j) {
        if(v[j] < v[i]) {
//            cout << "movi el " << v[i] << " porque estaba el " << v[j] << endl;
            v.push_back(v[i]);
            v.erase(v.begin() + i);
            return true;
        }
    }
    return false;
}

int main() {
    cin>>casos;
    int i = 1;
    while(casos--){
        cin>>n;
        vector<int> alturas(n);
        for(int i = 0; i<n ; i++) cin >> alturas[i];

        int sum = 0;
        for(int i = 0; i < n; i++) {
            auto num_pos = find(alturas.begin(), alturas.end(), i);
            int ind = num_pos - alturas.begin();
            if(desordenado(alturas, ind)) sum++;
        }
        cout << "Case " << i++ << ": " << sum << endl;

    }
    return 0;
}