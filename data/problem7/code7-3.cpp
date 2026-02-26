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
        
        // Read the adjacency matrix representing energy costs between towers
        vector<vector<int>> w(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> w[i][j];
            }
        }
        
        // Read the destruction order
        vector<int> destroy_order(n);
        for (int i = 0; i < n; i++) {
            cin >> destroy_order[i];
        }
        
        // Key insight: Process in reverse order (building up instead of tearing down)
        // This allows us to efficiently use Floyd-Warshall
        
        // Track which towers are currently "active" (not yet destroyed in forward time)
        vector<bool> active(n, false);
        
        // Store results for each destruction (we'll process in reverse)
        vector<long long> energy_per_step(n);
        
        // dist[i][j] will store the shortest path from tower i to tower j
        // considering only the currently active towers
        vector<vector<long long>> dist(n, vector<long long>(n));
        
        // Initialize distances with direct costs
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = w[i][j];
            }
        }
        
        // Process towers in reverse destruction order
        for (int step = n - 1; step >= 0; step--) {
            int k = destroy_order[step]; // This tower is being "added" (in reverse time)
            active[k] = true;
            
            // Update shortest paths using Floyd-Warshall with k as intermediate vertex
            // This updates all paths that might benefit from routing through tower k
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    // Check if path i -> k -> j is shorter than current i -> j
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
            
            // Calculate the sum of shortest paths between all active towers
            long long sum = 0;
            for (int i = 0; i < n; i++) {
                if (!active[i]) continue;
                for (int j = 0; j < n; j++) {
                    if (!active[j] || i == j) continue;
                    sum += dist[i][j];
                }
            }
            
            // Store the energy needed at this step
            energy_per_step[step] = sum;
        }
        
        // Calculate total energy
        // In forward time, when we destroy tower at position i,
        // we need energy_per_step[i] before destroying it
        long long total_energy = 0;
        for (int i = 0; i < n; i++) {
            total_energy += energy_per_step[i];
        }
        
        cout << total_energy << endl;
    }
    
    return 0;
}
