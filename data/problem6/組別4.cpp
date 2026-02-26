#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

/**
 * Computes the length of the Longest Increasing Subsequence (LIS)
 * using dynamic programming with binary search optimization.
 * Time Complexity: O(n log n)
 * 
 * @param sequence: The input sequence
 * @return: Length of the LIS
 */
int computeLIS(const vector<int>& sequence) {
    int n = sequence.size();
    if (n == 0) return 0;
    
    // tails[i] stores the smallest tail element for all increasing subsequences of length i+1
    vector<int> tails;
    
    for (int i = 0; i < n; i++) {
        // Find the position where sequence[i] should be inserted
        // to maintain sorted order in tails array
        auto it = lower_bound(tails.begin(), tails.end(), sequence[i]);
        
        if (it == tails.end()) {
            // sequence[i] is larger than all elements in tails
            // so it extends the longest subsequence
            tails.push_back(sequence[i]);
        } else {
            // Replace the element at position 'it' with sequence[i]
            // This maintains a smaller tail for subsequences of this length
            *it = sequence[i];
        }
    }
    
    // The size of tails array is the length of LIS
    return tails.size();
}

/**
 * Converts correct order C and student order R into permutation P,
 * then computes the LIS of P.
 * 
 * @param n: Number of events
 * @param C: Correct chronological order (C[i-1] = rank of event i)
 * @param R: Student's chronological order (R[i-1] = rank of event i)
 * @return: Length of LIS of permutation P
 */
int computeScore(int n, const vector<int>& C, const vector<int>& R) {
    // Step 1: Build inverse mapping of C
    // inv_C[k] = event number that has correct rank k
    // (converting from 1-indexed ranks to 0-indexed arrays)
    vector<int> inv_C(n + 1);
    for (int i = 0; i < n; i++) {
        int event = i + 1;        // Event number (1 to n)
        int rank = C[i];          // Correct rank of this event
        inv_C[rank] = event;      // Store which event has this rank
    }
    
    // Step 2: Build permutation P
    // P[k] = R[inv_C[k+1] - 1]
    // For position k in correct order, find which event should be there,
    // then find what rank the student gave to that event
    vector<int> P(n);
    for (int k = 0; k < n; k++) {
        int correctRank = k + 1;           // Correct rank (1 to n)
        int event = inv_C[correctRank];    // Which event has this correct rank
        int studentRank = R[event - 1];    // Student's rank for this event
        P[k] = studentRank;
    }
    
    // Step 3: Compute LIS of P
    return computeLIS(P);
}

int main() {
    string line;
    
    // Process multiple test cases
    while (getline(cin, line)) {
        // Read n (number of events)
        int n;
        stringstream ss(line);
        ss >> n;
        
        // Read correct chronological order C
        getline(cin, line);
        stringstream ss_c(line);
        vector<int> C(n);
        for (int i = 0; i < n; i++) {
            ss_c >> C[i];
        }
        
        // Process each student's order R until we encounter a new test case or EOF
        while (getline(cin, line)) {
            // Check if this line is a new test case (single integer for n)
            stringstream ss_check(line);
            vector<int> tokens;
            int token;
            while (ss_check >> token) {
                tokens.push_back(token);
            }
            
            // If line has only one token, it's a new test case
            if (tokens.size() == 1) {
                // Put the line back by processing it as new n
                n = tokens[0];
                
                // Read the new correct order
                getline(cin, line);
                stringstream ss_new_c(line);
                C.clear();
                C.resize(n);
                for (int i = 0; i < n; i++) {
                    ss_new_c >> C[i];
                }
                continue;
            }
            
            // This is a student's order R
            if (tokens.size() == (size_t)n) {
                vector<int> R = tokens;
                int score = computeScore(n, C, R);
                cout << score << endl;
            }
        }
    }
    
    return 0;
}
