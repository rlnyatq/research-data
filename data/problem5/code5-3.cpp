#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to check if it's possible to complete the trip with at most K nights
// such that no single day's walking distance exceeds maxDist
bool canComplete(const vector<int>& distances, int K, int maxDist) {
    int nightsUsed = 0;  // Number of camping nights used so far
    int currentDayDist = 0;  // Distance accumulated for the current day
    
    // Iterate through all distances
    for (int i = 0; i < distances.size(); i++) {
        // If adding this segment keeps us within the maxDist limit for today
        if (currentDayDist + distances[i] <= maxDist) {
            currentDayDist += distances[i];
        } 
        // Otherwise, we need to camp and start a new day
        else {
            // If a single segment is longer than maxDist, it's impossible
            if (distances[i] > maxDist) {
                return false;
            }
            
            // Camp here (use one night)
            nightsUsed++;
            
            // If we've used more nights than allowed, this maxDist doesn't work
            if (nightsUsed > K) {
                return false;
            }
            
            // Start a new day with the current segment
            currentDayDist = distances[i];
        }
    }
    
    // We successfully completed the trip within K nights
    return true;
}

int main() {
    int N, K;
    
    // Process multiple test cases until EOF
    while (cin >> N >> K) {
        vector<int> distances(N + 1);
        int totalDist = 0;
        int maxSegment = 0;
        
        // Read all N+1 distances
        for (int i = 0; i <= N; i++) {
            cin >> distances[i];
            totalDist += distances[i];
            maxSegment = max(maxSegment, distances[i]);
        }
        
        // Binary search on the answer
        // The minimum possible max daily distance is the longest single segment
        // (we must walk that segment in one day)
        int left = maxSegment;
        
        // The maximum possible max daily distance is walking everything in one day
        int right = totalDist;
        
        int answer = right;
        
        // Binary search to find the minimum feasible maximum daily distance
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Check if we can complete the trip with this max daily distance
            if (canComplete(distances, K, mid)) {
                // If yes, this is a valid answer; try to find a smaller one
                answer = mid;
                right = mid - 1;
            } else {
                // If no, we need a larger max daily distance
                left = mid + 1;
            }
        }
        
        cout << answer << endl;
    }
    
    return 0;
}
