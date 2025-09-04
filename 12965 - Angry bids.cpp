#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int angryBids(int bid, const vector<int>& P, const vector<int>& C) {
    int angry = 0;
    // Productores enojados si el precio es menor que su ideal
    angry += P.end() - lower_bound(P.begin(), P.end(), bid + 1);
    // Consumidores enojados si el precio es mayor que su ideal
    angry += upper_bound(C.begin(), C.end(), bid - 1) - C.begin();
    return angry;
}

int main() {
    int casos;
    cin >> casos;
    while (casos--) {
        int P, C;
        cin >> P >> C;
        vector<int> producers(P), consumers(C);
        
        for (int i = 0; i < P; i++) cin >> producers[i];
        for (int i = 0; i < C; i++) cin >> consumers[i];
        
        sort(producers.begin(), producers.end());
        sort(consumers.begin(), consumers.end());
        
        // Combinar precios candidatos (productores, consumidores y 0)
        vector<int> candidates;
        candidates.push_back(0);
        candidates.insert(candidates.end(), producers.begin(), producers.end());
        candidates.insert(candidates.end(), consumers.begin(), consumers.end());
        sort(candidates.begin(), candidates.end());
        candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
        
        int min_angry = INT_MAX;
        int best_price = 0;
        
        for (int price : candidates) {
            int current_angry = angryBids(price, producers, consumers);
            if (current_angry < min_angry || (current_angry == min_angry && price < best_price)) {
                min_angry = current_angry;
                best_price = price;
            }
        }
        
        cout << best_price << " " << min_angry << endl;
    }
    return 0;
}