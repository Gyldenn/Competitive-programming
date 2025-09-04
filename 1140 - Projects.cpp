#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//en este problema recibo un entero n, que indica la cantidad de proyectos
//despues los n pryectos tienen el dia de inicio, el de final, y la ganancia
//usando programacion dinamica debo devlver la mayor ganancia posible

long n;
vector<long> inicio,final, profit;

int main(){
    cin>>n;
    inicio.resize(n);
    final.resize(n);
    profit.resize(n);
    for(long i=0; i<n; i++){
        cin>>inicio[i]>>final[i]>>profit[i];
    }

    vector<long> idx(n);
    for (long i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](long a, long b) {
        return final[a] < final[b];
    });
    
    vector<long> inicio_ord(n), final_ord(n), profit_ord(n);
    for (long i = 0; i < n; i++) {
        inicio_ord[i] = inicio[idx[i]];
        final_ord[i] = final[idx[i]];
        profit_ord[i] = profit[idx[i]];
    }
    inicio = inicio_ord;
    final = final_ord;
    profit = profit_ord;    


    vector<long> dp(n+1, -1);
    vector<long> prev(n, -1);
    dp[0] = 0;
    for(long i=0; i<n; i++){
        for(long j=i-1; j>=0; j--){
            if(final[j] < inicio[i]){
                prev[i] = j;
                break;
            }
        }
    }
    for(long i=1; i<=n; i++){
        dp[i] = max(dp[i-1], profit[i-1] + (prev[i-1] == -1 ? 0 : dp[prev[i-1]+1]));
    }
    cout<<dp[n]<<endl;
    return 0;
}