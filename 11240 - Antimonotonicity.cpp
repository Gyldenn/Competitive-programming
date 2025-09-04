#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int casos, n;

int main() {
    cin >> casos;
    while (casos--) {
        cin >> n;
        vector<int> v(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        int k = v[0], ans = 1, fl=0, f;

        for(int i=1; i<n; i++){
            if(!fl){
                if(v[i]<k) {k=v[i];fl=1;f=1;ans++;}
                else k=max(k,v[i]);
            }
            else {
                if(f){
                    if(v[i]>k) {k=v[i];f^=1;ans++;}
                    else k=min(k,v[i]);
                }
                else {
                    if(v[i]<k) {k=v[i];f^=1;ans++;}
                    else k=max(k,v[i]);
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}