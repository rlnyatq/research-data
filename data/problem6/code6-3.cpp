#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to compute the length of the Longest Increasing Subsequence (LIS)
// using dynamic programming approach
int longestIncreasingSubsequence(const vector<int>& sequence) {
    int n = sequence.size();
    if (n == 0) return 0;
    
    // dp[i] represents the length of the longest increasing subsequence
    // ending at position i
    vector<int> dp(n, 1);
    
    // For each position i, check all previous positions j
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            // If sequence[j] < sequence[i], we can extend the subsequence ending at j
            if (sequence[j] < sequence[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    
    // Return the maximum length found
    return *max_element(dp.begin(), dp.end());
}

int main() {
    int n;
    
    // Process multiple test cases until EOF
    while (cin >> n) {
        // Read the correct chronological order
        // correctOrder[i] = the rank of event i in the correct timeline
        vector<int> correctOrder(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> correctOrder[i];
        }
        
        // Process each student's ranking
        while (true) {
            vector<int> studentRanking(n + 1);
            bool validInput = true;
            
            // Try to read a student's ranking
            for (int i = 1; i <= n; i++) {
                if (!(cin >> studentRanking[i])) {
                    validInput = false;
                    break;
                }
            }
            
            // If we couldn't read n integers, move to next test case
            if (!validInput) {
                break;
            }
            
            // Reconstruct the sequence of events as ordered by the student
            // studentSequence[i] = the event that the student placed at position i
            vector<int> studentSequence(n + 1);
            for (int event = 1; event <= n; event++) {
                int position = studentRanking[event];
                studentSequence[position] = event;
            }
            
            // Map the student's sequence to the correct chronological positions
            // This creates a sequence where we want to find the LIS
            vector<int> mappedSequence;
            for (int pos = 1; pos <= n; pos++) {
                int event = studentSequence[pos];
                int correctPosition = correctOrder[event];
                mappedSequence.push_back(correctPosition);
            }
            
            // Calculate and output the length of the longest increasing subsequence
            // This represents the maximum number of events in correct relative order
            int score = longestIncreasingSubsequence(mappedSequence);
            cout << score << endl;
        }
    }
    
    return 0;
}
