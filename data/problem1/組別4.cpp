#include <iostream>
#include <algorithm>
using namespace std;

// Function to calculate the cycle length L(n) for a given positive integer n
// This implements the Collatz conjecture algorithm
int calculateCycleLength(int n) {
    int length = 1; // Start with length 1 (counting the initial number)
    
    // Continue the algorithm until we reach 1
    while (n != 1) {
        if (n % 2 == 1) {
            // If n is odd: apply the rule n = 3*n + 1
            n = 3 * n + 1;
        } else {
            // If n is even: apply the rule n = n / 2
            n = n / 2;
        }
        length++; // Increment the count for each number in the sequence
    }
    
    return length;
}

// Function to compute M(i, j) = maximum cycle length for all integers in range [min(i,j), max(i,j)]
int computeMaxCycleLength(int i, int j) {
    // Ensure we work with the correct range [min, max]
    int minVal = min(i, j);
    int maxVal = max(i, j);
    
    int maxCycleLength = 0;
    
    // Iterate through all integers in the range [minVal, maxVal]
    for (int n = minVal; n <= maxVal; n++) {
        int cycleLength = calculateCycleLength(n);
        // Update the maximum cycle length found so far
        maxCycleLength = max(maxCycleLength, cycleLength);
    }
    
    return maxCycleLength;
}

int main() {
    int i, j;
    
    // Read input pairs until EOF (end of file)
    // Each line contains two integers i and j
    while (cin >> i >> j) {
        // Compute M(i, j) - the maximum cycle length in the range
        int result = computeMaxCycleLength(i, j);
        
        // Output: i j M(i,j)
        // Note: i and j are printed in the same order as input
        cout << i << " " << j << " " << result << endl;
    }
    
    return 0;
}
