#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * Function to check if it's possible to complete the trip with at most K nights
 * such that no single day's walking exceeds maxDist
 * 
 * @param distances: vector of distances between consecutive campsites
 * @param K: number of nights allowed
 * @param maxDist: maximum distance we're allowed to walk in a single day
 * @return true if feasible, false otherwise
 */
bool canComplete(const vector<int>& distances, int K, int maxDist) {
    int nights = 0;  // Number of nights we've camped so far
    int currentDayDist = 0;  // Distance walked on current day
    
    // Greedy approach: walk as far as possible each day without exceeding maxDist
    for (int i = 0; i < distances.size(); i++) {
        // If a single segment is longer than maxDist, it's impossible
        if (distances[i] > maxDist) {
            return false;
        }
        
        // If adding this segment exceeds maxDist, we must camp before it
        if (currentDayDist + distances[i] > maxDist) {
            // Camp at the previous campsite (end current day)
            nights++;
            currentDayDist = distances[i];  // Start new day with current segment
        } else {
            // Continue walking on the same day
            currentDayDist += distances[i];
        }
    }
    
    // Check if we used at most K nights
    return nights <= K;
}

int main() {
    int N, K;
    
    // Process multiple test cases
    while (cin >> N >> K) {
        vector<int> distances(N + 1);
        int totalDist = 0;
        int maxSegment = 0;
        
        // Read all distances
        for (int i = 0; i <= N; i++) {
            cin >> distances[i];
            totalDist += distances[i];
            maxSegment = max(maxSegment, distances[i]);
        }
        
        // Binary search on the answer
        // Lower bound: the longest single segment (we must walk this in one day)
        // Upper bound: total distance (walk everything in one day)
        int left = maxSegment;
        int right = totalDist;
        int answer = totalDist;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Check if we can complete trip with max daily distance = mid
            if (canComplete(distances, K, mid)) {
                // If feasible, try to find a smaller maximum
                answer = mid;
                right = mid - 1;
            } else {
                // If not feasible, we need a larger maximum
                left = mid + 1;
            }
        }
        
        cout << answer << endl;
    }
    
    return 0;
}
