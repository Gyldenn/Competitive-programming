#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>
#include <tuple>

using namespace std;

int n;
vector<int> res;

tuple<int, int> maxDigitoYPosicion(int n, int len) {
    int max_digito = -1;
    int pos_max = -1;
    int pos = 0;
    int potencia = 1;

    for (int i = len - 1; i >= 0; --i) {
        int divisor = 1;
        for (int j = 0; j < i; ++j)
            divisor *= 10;
        int digito = (n / divisor) % 10;
        if (digito > max_digito) {
            max_digito = digito;
            pos_max = pos;
            if ( digito == 9) break;
        }
        ++pos;
    }

    return {max_digito, pos_max};
}

int subseq(int num, int pos) {
    string s = to_string(num);
    string sub = s.substr(pos);
    return stoi(sub);
}

int backtracking(int n) {
    if (n == 0) return 0;
    int res;

    int temp = n;
    int len = 0;
    while (temp > 0) {++len; temp /= 10;}

    tuple<int,int> sol = maxDigitoYPosicion(n, len);
    int num = subseq(n, get<1>(sol));
    int cociente = num / get<0>(sol);
    res = cociente + 1;
    res += backtracking(n- (cociente+1)*get<0>(sol));
    return res;
}

int main() {
    while(cin>>n) cout<<backtracking(n);
    return 0;
}
