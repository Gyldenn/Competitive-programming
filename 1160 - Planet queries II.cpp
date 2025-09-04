#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int N = 2e5 + 5, M = 20;
int sh[N][M], A[N], D[N], L;

void dfs(int u) {
    if(u < 1 || u >= N || A[u]) return;
    A[u] = 1;
    dfs(sh[u][0]);
    D[u] = D[sh[u][0]] + 1;
}

int yd(int x, int y) {
    for(int i = 0; i < M; i++) {
        if(y & (1 << i)) {
            if(x < 1 || x >= N) return -1; // Evitar acceso inválido
            x = sh[x][i];
        }
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, q;
    cin >> n >> q;
    L = ceil(log2(n)) + 1;
    
    for(int i = 1; i <= n; i++) cin >> sh[i][0];
    
    for(int j = 1; j < M; j++) {
        for(int i = 1; i <= n; i++) {
            sh[i][j] = sh[sh[i][j-1]][j-1];
        }
    }
    
    for(int i = 1; i <= n; i++) if(!A[i]) dfs(i);
    
    while(q--) {
        int x, y;
        cin >> x >> y;
        
        if(x == y) {
            cout << "0\n";
            continue;
        }
        
        int ans = -1;
        // intento llegar yendo hacia arriba
        if(D[x] >= D[y]) {
            int candidate = yd(x, D[x] - D[y]);
            if(candidate == y) ans = D[x] - D[y];
        }
        // Si no funciona, pruebo otra estrategia
        if(ans == -1) {
            int zd = yd(x, D[x]);
            int candidate = yd(zd, D[zd] - D[y]);
            if(candidate == y) ans = D[x] + D[zd] - D[y];
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}