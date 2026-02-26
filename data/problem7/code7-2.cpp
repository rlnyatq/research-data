#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        // Read the adjacency matrix (communication costs)
        vector<vector<int>> w(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> w[i][j];
            }
        }
        
        // Read the destruction order
        vector<int> order(n);
        for (int i = 0; i < n; i++) {
            cin >> order[i];
        }
        
        // Key insight: Process in REVERSE order (building up instead of destroying)
        // This allows us to use Floyd-Warshall incrementally
        
        // Distance matrix - initially set to the original weights
        vector<vector<long long>> dist(n, vector<long long>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = w[i][j];
            }
        }
        
        // Track which towers are currently active (in reverse, we're adding them)
        vector<bool> active(n, false);
        
        // Store energies for each destruction (in reverse order)
        vector<long long> energies(n);
        
        // Process towers in reverse order
        for (int step = n - 1; step >= 0; step--) {
            int k = order[step]; // Tower being added back
            active[k] = true;
            
            // Update shortest paths using this tower as intermediate node
            // Floyd-Warshall update with tower k
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
            
            // Calculate total energy needed with current active towers
            long long energy = 0;
            for (int i = 0; i < n; i++) {
                if (active[i]) {
                    for (int j = 0; j < n; j++) {
                        if (active[j] && i != j) {
                            energy += dist[i][j];
                        }
                    }
                }
            }
            
            energies[step] = energy;
        }
        
        // Sum all energies (the energy needed at each destruction step)
        long long totalEnergy = 0;
        for (int i = 0; i < n; i++) {
            totalEnergy += energies[i];
        }
        
        cout << totalEnergy << endl;
    }
    
    return 0;
}
