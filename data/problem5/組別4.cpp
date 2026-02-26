#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Check if it's feasible to complete the trip with maximum daily distance <= maxDist
 * using exactly K nights (stopping at K campsites).
 * 
 * Strategy: Greedy approach - travel as far as possible each day without exceeding maxDist.
 * If we can complete the trip in K or fewer nights, it's feasible.
 */
bool isFeasible(const vector<int>& a, int N, int K, int maxDist) {
    int nightsUsed = 0;      // Number of nights (campsite stops) used so far
    int currentDayDist = 0;  // Distance accumulated in current day
    
    // Iterate through all N+1 segments
    for (int i = 0; i <= N; i++) {
        // If a single segment exceeds maxDist, it's impossible
        if (a[i] > maxDist) {
            return false;
        }
        
        // Try to add segment a[i] to current day
        if (currentDayDist + a[i] <= maxDist) {
            // Can continue walking today
            currentDayDist += a[i];
        } else {
            // Must stop at a campsite (end current day)
            // This means we stop at campsite i (just before segment a[i])
            nightsUsed++;
            
            // Start new day with segment a[i]
            currentDayDist = a[i];
            
            // If we've used more than K nights, it's not feasible
            if (nightsUsed > K) {
                return false;
            }
        }
    }
    
    // We completed the trip using nightsUsed nights
    // It's feasible if we used at most K nights
    return nightsUsed <= K;
}

/**
 * Find the minimum possible maximum daily walking distance M*
 * using binary search on the answer.
 */
int findMinMaxDistance(const vector<int>& a, int N, int K) {
    // Binary search bounds
    // Lower bound: The maximum single segment (we must walk at least this far in some day)
    int left = *max_element(a.begin(), a.end());
    
    // Upper bound: Sum of all segments (walk everything in one day)
    int right = 0;
    for (int i = 0; i <= N; i++) {
        right += a[i];
    }
    
    int result = right;  // Initialize with upper bound
    
    // Binary search for the minimum feasible maxDist
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (isFeasible(a, N, K, mid)) {
            // If mid is feasible, try to find a smaller value
            result = mid;
            right = mid - 1;
        } else {
            // If mid is not feasible, we need a larger maxDist
            left = mid + 1;
        }
    }
    
    return result;
}

int main() {
    int N, K;
    
    // Process multiple test cases until EOF
    while (cin >> N >> K) {
        vector<int> a(N + 1);  // N+1 segments: a[0] to a[N]
        
        // Read the N+1 distance values
        for (int i = 0; i <= N; i++) {
            cin >> a[i];
        }
        
        // Compute and output the minimum maximum daily distance
        int result = findMinMaxDistance(a, N, K);
        cout << result << endl;
    }
    
    return 0;
}
