#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Check if we can complete the trip in at most K+1 days
// with maximum daily distance <= maxDist
bool canComplete(const vector<int>& distances, int K, int maxDist) {
    int days = 1;  // Start with day 1
    int currentDist = 0;
    
    for (int i = 0; i < distances.size(); i++) {
        // If a single segment is longer than maxDist, impossible
        if (distances[i] > maxDist) {
            return false;
        }
        
        // If adding this segment exceeds maxDist, start a new day
        if (currentDist + distances[i] > maxDist) {
            days++;
            currentDist = distances[i];
            
            // If we need more than K+1 days, it's not feasible
            if (days > K + 1) {
                return false;
            }
        } else {
            currentDist += distances[i];
        }
    }
    
    return true;
}

int main() {
    int N, K;
    
    while (cin >> N >> K) {
        vector<int> distances(N + 1);
        int totalDist = 0;
        int maxSegment = 0;
        
        for (int i = 0; i <= N; i++) {
            cin >> distances[i];
            totalDist += distances[i];
            maxSegment = max(maxSegment, distances[i]);
        }
        
        // Binary search on the answer
        int left = maxSegment;  // At minimum, we need to handle the longest segment
        int right = totalDist;   // At maximum, we walk everything in one day
        int answer = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canComplete(distances, K, mid)) {
                answer = mid;
                right = mid - 1;  // Try to find smaller maximum
            } else {
                left = mid + 1;   // Need larger maximum
            }
        }
        
        cout << answer << endl;
    }
    
    return 0;
}
