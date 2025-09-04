#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Basado en la referencia de "11951 - Area.cpp"
pair<int, int> maxAreaSubmatriz(const vector<vector<int>> &mat, int maxSaldo) {
    int n = mat.size(), m = mat[0].size();
    // sum[i][j]: suma de la columna j desde la fila 0 hasta la fila i-1
    vector<vector<int>> sum(n + 1, vector<int>(m, 0));
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < m; ++j)
            sum[i][j] = sum[i - 1][j] + mat[i - 1][j];

    int maxArea = 0, minSum = INT_MAX;

    for (int r1 = 1; r1 <= n; ++r1) {
        for (int r2 = r1; r2 <= n; ++r2) {
            int c1 = 0, currSum = 0;
            for (int c2 = 0; c2 < m; ++c2) {
                currSum += sum[r2][c2] - sum[r1 - 1][c2];
                while (c1 <= c2 && currSum > maxSaldo) {
                    currSum -= sum[r2][c1] - sum[r1 - 1][c1];
                    ++c1;
                }
                int area = (r2 - r1 + 1) * (c2 - c1 + 1);
                if (currSum <= maxSaldo) {
                    if (area > maxArea || (area == maxArea && currSum < minSum)) {
                        maxArea = area;
                        minSum = currSum;
                    }
                }
            }
        }
    }
    if (maxArea == 0) minSum = 0;
    return {maxArea, minSum};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int casos;
    cin >> casos;
    for (int caso = 1; caso <= casos; ++caso) {
        int n, m, maxSaldo;
        cin >> n >> m >> maxSaldo;
        vector<vector<int>> mat(n, vector<int>(m));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                cin >> mat[i][j];
        auto res = maxAreaSubmatriz(mat, maxSaldo);
        cout << "Case #" << caso << ": " << res.first << " " << res.second << endl;
    }
    return 0;
}