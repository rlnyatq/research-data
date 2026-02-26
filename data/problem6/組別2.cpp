#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

// Function to compute the Longest Increasing Subsequence (LIS)
// Uses dynamic programming with O(n^2) time complexity
int computeLIS(const vector<int>& sequence) {
    int n = sequence.size();
    if (n == 0) return 0;
    
    // dp[i] stores the length of the longest increasing subsequence
    // that ends with sequence[i]
    vector<int> dp(n, 1);
    
    // Build up the LIS lengths
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (sequence[j] < sequence[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    
    // The answer is the maximum LIS length
    return *max_element(dp.begin(), dp.end());
}

int main() {
    int n;
    
    // Process each test case
    while (cin >> n) {
        // Store the correct position for each event
        // correctPos[event] = position where event should be
        vector<int> correctPos(n + 1);
        
        // Read correct chronological order
        for (int pos = 1; pos <= n; pos++) {
            int event;
            cin >> event;
            correctPos[event] = pos;
        }
        
        // Process each student's answer
        // Continue reading lines of n integers until we can't read n integers
        vector<int> studentRanking(n);
        while (true) {
            bool success = true;
            for (int i = 0; i < n; i++) {
                if (!(cin >> studentRanking[i])) {
                    success = false;
                    break;
                }
            }
            
            if (!success) break;
            
            // Map the student's ranking to correct positions
            // The student lists events in their perceived chronological order
            // We map each event to its correct chronological position
            vector<int> mappedSequence(n);
            for (int i = 0; i < n; i++) {
                int event = studentRanking[i];
                mappedSequence[i] = correctPos[event];
            }
            
            // Find and output the LIS length
            cout << computeLIS(mappedSequence) << endl;
        }
        
        // Clear error state for next test case
        cin.clear();
    }
    
    return 0;
}
