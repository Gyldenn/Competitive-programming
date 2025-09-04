#include <bits/stdc++.h>
#define mem(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10005;

int f[maxn * 2];

int find(int x) {
    return (f[x] == x) ? x : find(f[x]);
}

int main() {
    int n;
    while (~scanf("%d", &n)) {
        for (int i = 0; i <= 2 * n; i++) {
            f[i] = i;
        }
        int c, a, b;
        while (~scanf("%d%d%d", &c, &a, &b)) {
            if (a == 0 && b == 0 && c == 0) break;
            int fa = find(a), ea = find(a + n);
            int fb = find(b), eb = find(b + n);
            if (c == 1) {
                if (fa == eb) printf("-1\n");
                else {
                    f[fa] = fb;
                    f[ea] = eb;
                }
            } else if (c == 2) {
                if (fa == fb) printf("-1\n");
                else {
                    f[fa] = eb;
                    f[ea] = fb;
                }
            } else if (c == 3) {
                if (fa == fb) printf("1\n");
                else printf("0\n");
            } else {
                if (fa == eb) printf("1\n");
                else printf("0\n");
            }
        }
    }
    return 0;
}