#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<vector<long long>> w(n, vector<long long>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> w[i][j];
            }
        }
        
        vector<int> order(n);
        for (int i = 0; i < n; i++) {
            cin >> order[i];
        }
        
        // Process in reverse order (adding towers instead of removing)
        vector<long long> energies;
        vector<bool> active(n, false);
        vector<vector<long long>> dist = w;
        
        for (int idx = n - 1; idx >= 0; idx--) {
            int k = order[idx];
            active[k] = true;
            
            // Update shortest paths using Floyd-Warshall with new tower k
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
            
            // Calculate sum of distances between all active towers
            long long sum = 0;
            for (int i = 0; i < n; i++) {
                if (!active[i]) continue;
                for (int j = 0; j < n; j++) {
                    if (i != j && active[j]) {
                        sum += dist[i][j];
                    }
                }
            }
            
            energies.push_back(sum);
        }
        
        // Reverse to get the correct order
        reverse(energies.begin(), energies.end());
        
        long long totalEnergy = 0;
        for (long long e : energies) {
            totalEnergy += e;
        }
        
        cout << totalEnergy << endl;
    }
    
    return 0;
}
