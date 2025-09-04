#include <bits/stdc++.h>
using namespace std;

int m, n;
vector<int> objects; // Representa los objetos como ints
map<set<int>, int> memo;

int dfs(set<int> s) {
    if (s.size() <= 1) return 0;
    if (memo.count(s)) return memo[s];

    int res = INT_MAX;

    for (int bit = 0; bit < m; ++bit) {
        set<int> zero, one;
        for (int obj : s) {
            if (obj & (1 << bit))
                one.insert(obj);
            else
                zero.insert(obj);
        }

        // Si no divide, no sirve
        if (zero.empty() || one.empty()) continue;

        int tmp = max(dfs(zero), dfs(one)) + 1;
        res = min(res, tmp);
    }

    return memo[s] = res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> m >> n && (m || n)) {
        objects.clear();
        memo.clear();

        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            int val = 0;
            for (int j = 0; j < m; ++j) {
                if (s[j] == '1')
                    val |= (1 << (m - j - 1));
            }
            objects.push_back(val);
        }

        set<int> all(objects.begin(), objects.end());
        cout << dfs(all) << '\n';
    }

    return 0;
}
