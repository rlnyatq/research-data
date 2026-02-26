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
        
        // Read the weight matrix w(i, j)
        vector<vector<long long>> w(n, vector<long long>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> w[i][j];
            }
        }
        
        // Read the destruction order
        vector<int> destruction_order(n);
        for (int i = 0; i < n; i++) {
            cin >> destruction_order[i];
        }
        
        // d[i][j] will store the minimum energy (shortest path) from tower i to tower j
        // Initialize with the direct edge weights
        vector<vector<long long>> d(n, vector<long long>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = w[i][j];
            }
        }
        
        // Track which towers are currently active (not yet destroyed)
        vector<bool> is_active(n, false);
        
        // Store the power values P_k for each step
        // We'll compute them in reverse order
        vector<long long> power_values;
        
        long long total_energy = 0;
        
        // Process towers in REVERSE order of destruction
        // This way we're "adding" towers instead of removing them
        for (int step = n - 1; step >= 0; step--) {
            int new_tower = destruction_order[step];
            
            // Mark this tower as active
            is_active[new_tower] = true;
            
            // Update shortest paths using the newly added tower as intermediate node
            // This is the incremental Floyd-Warshall update
            // For all pairs (i, j), check if path i -> new_tower -> j is shorter
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (d[i][new_tower] + d[new_tower][j] < d[i][j]) {
                        d[i][j] = d[i][new_tower] + d[new_tower][j];
                    }
                }
            }
            
            // Calculate P_k: sum of all shortest paths between active towers
            long long current_power = 0;
            for (int i = 0; i < n; i++) {
                if (!is_active[i]) continue;
                for (int j = 0; j < n; j++) {
                    if (!is_active[j] || i == j) continue;
                    current_power += d[i][j];
                }
            }
            
            // Store this power value (we'll sum them later)
            power_values.push_back(current_power);
        }
        
        // Since we processed in reverse order, sum all power values
        // power_values[0] corresponds to when all towers are present (P_1)
        // power_values[n-1] corresponds to when only the last tower remains (P_n = 0)
        for (long long p : power_values) {
            total_energy += p;
        }
        
        cout << total_energy << endl;
    }
    
    return 0;
}
